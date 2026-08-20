# msKPP 开发指南

<br>

本文档介绍 msKPP（MindStudio Kernel Performance Prediction）的开发环境搭建、编译构建及 UT 单元测试方法。

## 1. 前置条件

### 1.1 知识准备

开发前请先阅读《[msKPP 架构设计文档](./architecture.md)》，了解代码框架及核心流程。

### 1.2 环境准备

按照《[msKPP 安装指南 — 源码安装](../install_guide/mskpp_install_guide.md#231-环境准备)》章节完成编译和测试环境的搭建。

> **说明：** 环境镜像的构建方法及配套软件版本由 MindStudio 统一镜像制作指南维护，本仓库不重复定义。

## 2. 编译构建

在项目根目录执行：

```bash
python3 build.py
```

### 2.1 构建产物

构建成功后，输出将生成在 `artifacts` 目录下。

### 2.2 清理构建

如需全量重新编译，删除构建目录后重新执行上述步骤：

```bash
rm -rf build
```

## 3. 单元测试

### 3.1 执行测试

```bash
python3 build.py test
```

全部通过时输出类似如下示例：

```text
[==========] 37 tests from 6 test cases ran. (616 ms total)
[  PASSED  ] 37 tests.
```

> **判定标准：** `ran` 的用例数与 `PASSED` 的用例数一致即为通过。若存在 `FAILED` 用例，请根据日志定位失败原因。

### 3.2 清理测试环境

删除 UT 构建目录后重新执行测试：

```bash
rm -rf build_ut
```
