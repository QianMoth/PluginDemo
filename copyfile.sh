#!/bin/bash
cur_path=$(readlink -f "$(dirname "$0")")
echo $cur_path

find $cur_path/build/bin/  -name "*d.dll" -exec cp {} $cur_path/../nodeeditor*/build/bin/Debug/nodes/ \;
find $cur_path/build/bin/ ! -name "*d.dll" -a -name "*.dll" -exec cp {} $cur_path/../nodeeditor*/build/bin/Release/nodes/ \;
