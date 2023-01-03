<center><h1 style="text-transform:uppercase;">PLUGIN_DEMO</h1></center>

<!-- 目录 -->
# Contents
- [Contents](#contents)
- [Overview](#overview)
- [Build \& Install](#build--install)
  - [Dependencies](#dependencies)
  - [Build](#build)
  - [Install](#install)
- [Origin \& References](#origin--references)
- [Show](#show)

# Overview



# Build & Install
## Dependencies

Qt >= 5.15.2

## Build

> 不要出现中文路径！

```bash
git clone https://github.com/QianMoth/PluginDemo.git
cd PluginDemo
mkdir build

# Release
cmake -S . -Bbuild -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release

# Debug
cmake -S . -Bbuild -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug
```
## Install

build结束你可以在./build/bin/文件夹下看到pluginbase.dll和pluginbased.dll。

你可以直接复制粘贴到你的插件目录下,也可以通过修改copyfile.sh来安装到指定目录。

如果你是windows用户，在执行shell脚本需要考虑是否安装了能执行shell的工具，如git。

```bash
#!/bin/bash

cur_path=$(readlink -f "$(dirname "$0")")
# 打印当前文件路径
echo $cur_path

# 找到结尾有d的dll文件安装到Debug目录
find $cur_path/build/bin/  -name "*d.dll" -exec cp {} $cur_path/../nodeeditor/build/bin/Debug/nodes/ \;

# 找到结尾没有d的dll文件安装到Debug目录
find $cur_path/build/bin/ ! -name "*d.dll" -a -name "*.dll" -exec cp {} $cur_path/../nodeeditor/build/bin/Release/nodes/ \;
```

# Origin & References

- [nodeeditor](https://github.com/paceholder/nodeeditor.git)


# Show
