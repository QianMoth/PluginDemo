# 1. PLUGIN_DEMO
[中文](./README.md) | [English](./README_EN.md)<br>
> This is a plug-in demo and a test case

<!-- 目录 -->
- [1. PLUGIN\_DEMO](#1-plugin_demo)
  - [1.1. Overview](#11-overview)
  - [1.2. Build \& Install](#12-build--install)
    - [1.2.1. Dependencies](#121-dependencies)
    - [1.2.2. Build](#122-build)
    - [1.2.3. Install](#123-install)
  - [1.3. Origin \& References](#13-origin--references)
  - [1.4. Show](#14-show)

## 1.1. Overview

Plug-in demo, some functions of the use of methods

## 1.2. Build & Install
### 1.2.1. Dependencies

Qt 5.15.2

### 1.2.2. Build

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
### 1.2.3. Install

You can see `plugindemo.dll` and `plugindemod.dll` in the `./build/bin/` folder.

You can either copy and paste it directly into your plugin directory or install it in a specific directory by modifying **copyfile.sh**.

If you are a windows user, you need to consider whether you have installed tools that can execute shell scripts, such as **git**.

```bash
#!/bin/bash

cur_path=$(readlink -f "$(dirname "$0")")
# Prints the current file path
echo $cur_path

# Find the dll file with d at the end and install it in the Debug directory
find $cur_path/build/bin/  -name "*d.dll" -exec cp {} $cur_path/../nodeeditor-p/build/bin/Debug/nodes/ \;

# Find the dll file without d at the end and install it into the Debug directory
find $cur_path/build/bin/ ! -name "*d.dll" -a -name "*.dll" -exec cp {} $cur_path/../nodeeditor-p/build/bin/Release/nodes/ \;
```

## 1.3. Origin & References

- [nodeeditor](https://github.com/paceholder/nodeeditor.git)
- [spkgen](https://github.com/fredakilla/spkgen.git)


## 1.4. Show

![node](./pictures/node.png)