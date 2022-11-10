#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
QMK_HOME=~/qmk_firmware

rsync -av $DIR/root/keyboards/rwkb/ $QMK_HOME/keyboards/rwkb/ --delete
compile(){
  qmk compile -kb $1 -km default
  local name=${1//\//_}
  local src=$QMK_HOME/${name}_default.$2
  local dst=${name}_$(md5sum $src | cut -d' ' -f1).$2
  echo src: $src 
  echo dst: $dst

  # copy to here
  cp $src $DIR/output/$dst
  # share it on public folder
  cp $src /home/public/developer/$dst

}

compile "rwkb/teensy" "hex"
compile "rwkb/jj40" "hex"
compile "rwkb/planck/rev6" "bin"

echo "flash with: qmk flash -kb <name>"
