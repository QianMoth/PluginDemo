# 1. PLUGIN_DEMO

这是一个插件的demo，也是测试用例。

<!-- 注释 -->
- [1. PLUGIN_DEMO](#1-plugin_demo)
  - [1.1. Dependencies](#11-dependencies)
  - [1.2. Build](#12-build)
  - [1.3. Show](#13-show)

## 1.1. Dependencies

Qt 5.15.2

## 1.2. Build

```shell
cd PluginDemo
mkdir build

cmake -S . -Bbuild -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

## 1.3. Show

node预览
![node](./pictures/node.png)