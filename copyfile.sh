#!/bin/bash
cur_path=$(readlink -f "$(dirname "$0")")
# 打印当前文件路径
echo $cur_path

# 找到结尾有d的dll文件安装到Debug目录
find $cur_path/build/bin/  -name "*d.dll" -exec cp {} $cur_path/../nodeeditor-p/build/bin/Debug/nodes/ \;
# 找到结尾没有d的dll文件安装到Debug目录
find $cur_path/build/bin/ ! -name "*d.dll" -a -name "*.dll" -exec cp {} $cur_path/../nodeeditor-p/build/bin/Release/nodes/ \;
