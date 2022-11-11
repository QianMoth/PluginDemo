#!/bin/bash
cur_path=$(readlink -f "$(dirname "$0")")
# 打印当前文件路径
echo $cur_path

find $cur_path/build/bin/  -name "*.dll" -exec rm {} \;
find $cur_path/build/bin/  -name "*.pdb" -exec rm {} \;


