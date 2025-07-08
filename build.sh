#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
KEYBOARD=yourkeyboard
KEYMAP=yourmap

podman run --rm -it \
  -v "$REPO_DIR:/home/builder/qmk_firmware/keyboards/$KEYBOARD" \
  -w /home/builder/qmk_firmware \
  qmk-builder \
  qmk compile -kb $KEYBOARD -km $KEYMAP

