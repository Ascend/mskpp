# MindStudio Kernel Performance Prediction 开发环境搭建及编译和UT方法

<br>

## 1. 预备知识

请参考[《msKPP 架构设计文档》](./architecture.md)学习代码框架及核心流程。

## 2. 开发环境准备

- 硬件环境请参见《[昇腾产品形态说明](https://www.hiascend.com/document/detail/zh/AscendFAQ/ProduTech/productform/hardwaredesc_0001.html)》。

- 请按照以下文档进行环境配置：[《算子工具开发环境安装指导》](https://gitcode.com/Ascend/msot/blob/master/docs/zh/common/dev_env_setup.md)。

- 要求构建环境中安装python3.9或以上版本。

- mskpp需要依赖其他python库。通过pip install -r requirement.txt一键式安装依赖库。
- `gcc 版本 > 7.4.0`  
- `3.20.2 <= CMAKE版本 <= 3.31.10`

## 3. 编译打包

分为如下两种方式，优缺点如下：

| 方法 | 适用场景 | 优点 | 缺点 |
|------|---------|------|------|
| 一键式脚本 | 首次构建、CI/CD 流水线 | 零配置，一步到位 | 无法单独执行某一步骤 |
| 分步骤脚本 | 日常开发、增量编译 | 灵活，效率高 | 需要多步操作 |

### 3.1 方法一：一键式脚本

```shell
python build.py
```

### 3.2 方法二：分步骤脚本

#### 3.2.1 编译打包

```shell
mkdir build
cd build
cmake ..
make -j$(nproc) install # -j 是并行编译的 job 数量，可自行指定；nproc 不可用时请手动填数字（例如 -j8）。
```

##### 3.2.1.2 编译结果说明

编译结果生成到 output 目录下：

```text
output/
|-- include                                              # API接口头文件
|-- lib                                                  # 静态库
|-- lib64                                                # 动态库
|-- mindstudio_kpp-XXX-py3-none-manylinux_2_31_XXX.whl   # 安装包
```

#### 3.2.3 清理/重新编译

删除构建目录，重新执行[第 3.2.1 节](#321-编译打包)：   

```shell
rm -rf build
```

## 4. 执行UT测试

### 4.1 一键式脚本

python的UT测试，依赖pytest和coverage工具，可通过执行 ```pip install coverage pytest``` 安装

```shell
python build.py test
```

输出类似如下跑的用例数和通过用例数相同即表示成功：

```text
[==========] 37 tests from 6 test cases ran. (616 ms total)
[  PASSED  ] 37 tests.
```

### 4.2 清理/重新编译

删除构建目录，重新执行[第 4.1 节](#41-一键式脚本)：   

```shell
rm -rf build_ut  
```
