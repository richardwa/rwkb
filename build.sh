#!/usr/bin/env bash
#
# build.sh - build QMK firmware for all keyboards via podman
#
# Usage:
#   ./build.sh                 build all keyboards
#   ./build.sh planck          build keyboards whose name matches pattern(s)
#
# Everything transient lives under build/:
#   build/cache/qmk_firmware   shallow QMK source clone (cached across runs)
#   build/output/              finished firmware binaries (.bin/.hex)
#
set -euo pipefail

QMK_IMAGE="ghcr.io/qmk/qmk_cli:latest"
BUILD_DIR="build"
CACHE_DIR="$BUILD_DIR/cache"
OUT_DIR="$BUILD_DIR/output"
FW_DIR="$CACHE_DIR/qmk_firmware"
QMK_REPO="https://github.com/qmk/qmk_firmware.git"

# Auto-discover configurator keymap exports (they have a "keyboard" field).
# Plain VIA layout exports (e.g. the Epomaker Luma40) are skipped.
KEYMAPS=()
for f in config/*.json; do
    if python3 -c 'import json,sys; json.load(open(sys.argv[1]))["keyboard"]' "$f" >/dev/null 2>&1; then
        KEYMAPS+=("$f")
    fi
done

if [[ $# -gt 0 ]]; then
    filtered=()
    for f in "${KEYMAPS[@]}"; do
        for pat in "$@"; do
            [[ "$f" == *"$pat"* ]] && filtered+=("$f") && break
        done
    done
    KEYMAPS=("${filtered[@]}")
fi

if [[ ${#KEYMAPS[@]} -eq 0 ]]; then
    echo "No matching keymaps found in config/." >&2
    exit 1
fi

mkdir -p "$CACHE_DIR" "$OUT_DIR"

# --- container image (cached) ------------------------------------------------
if ! podman image exists "$QMK_IMAGE"; then
    echo "==> Pulling $QMK_IMAGE"
    podman pull "$QMK_IMAGE"
fi

# --- QMK firmware source (cached) --------------------------------------------
if [[ -d "$FW_DIR/.git" ]]; then
    echo "==> Updating cached QMK source"
    git -C "$FW_DIR" fetch --depth 1 origin master
    git -C "$FW_DIR" reset --hard FETCH_HEAD
else
    echo "==> Cloning QMK source (shallow)"
    git clone --depth 1 --recurse-submodules --shallow-submodules "$QMK_REPO" "$FW_DIR"
fi

# --- podman invocation -------------------------------------------------------
# Rootless podman maps container root to the host user, so files written to
# the mounts are owned by us. QMK_HOME points qmk at the cached source tree.
qmk() {
    podman run --rm \
        -v "$PWD":/work:Z \
        -v "$PWD/$FW_DIR":/qmk_firmware:Z \
        -e QMK_HOME=/qmk_firmware \
        -w /work \
        "$QMK_IMAGE" \
        sh -c "$*"
}

# --- build -------------------------------------------------------------------
FAILED=()
for keymap_json in "${KEYMAPS[@]}"; do
    name="$(basename "$keymap_json" .json)"
    keyboard="$(python3 -c 'import json,sys; print(json.load(open(sys.argv[1]))["keyboard"])' "$keymap_json")"
    keymap="$(python3 -c 'import json,sys; print(json.load(open(sys.argv[1]))["keymap"])' "$keymap_json")"

    echo "==> Building $name ($keyboard:$keymap)"

    # qmk copies the keymap into the source tree; remove any stale copy first
    if ! qmk "rm -rf /qmk_firmware/keyboards/$keyboard/keymaps/$keymap && qmk compile '$keymap_json'"; then
        echo "!! FAILED: $name" >&2
        FAILED+=("$name")
        continue
    fi

    # The artifact lands in the repo root (or firmware root depending on qmk
    # version); move whatever was produced into build/output.
    artifact=""
    for ext in bin hex uf2; do
        for dir in . "$FW_DIR"; do
            cand="$dir/$keymap.$ext"
            [[ -f "$cand" ]] && artifact="$cand" && break 2
        done
    done

    if [[ -n "$artifact" ]]; then
        mv -f "$artifact" "$OUT_DIR/"
        echo "    -> $OUT_DIR/$(basename "$artifact")"
    else
        echo "!! Compiled but no firmware artifact found for $name" >&2
        FAILED+=("$name")
    fi
done

echo
echo "==> Firmware in $OUT_DIR:"
ls -1 "$OUT_DIR"

if [[ ${#FAILED[@]} -gt 0 ]]; then
    echo
    echo "!! Failed: ${FAILED[*]}" >&2
    exit 1
fi
