# MindStudio Kernel Performance Prediction 安装指南

<br>

## 1. 安装说明

msKPP工具的安装方式包括：

- 二进制安装：msKPP工具完整功能已集成在CANN包中发布，可直接安装CANN包，请参考《[CANN 官方安装指南](https://www.hiascend.com/cann/download)》，按文档逐步完成安装与配置。
- 源码安装：如需使用最新代码的功能，或对源码进行修改以增强功能，可下载本仓库代码，自行编译、打包工具并完成安装，具体请参见[源码安装](#2-源码安装)。

## 2. 源码安装

如需使用最新代码的功能，或对源码进行修改以增强功能，可下载本仓库代码，自行编译、打包工具并完成安装。

### 2.1 环境准备

请按照以下文档进行环境配置：《[算子工具开发环境安装指导](https://gitcode.com/Ascend/msot/blob/26.0.0/docs/zh/common/dev_env_setup.md)》。

要求构建环境中安装`python3.9`及以上版本才能正常运行。

mskpp需要依赖其他python库。通过`pip install -r requirements.txt`一键式安装依赖库。
依赖库列表如下

```text
plotly>=5.11.0
```

### 2.2 执行编译打包

通过一键式脚本自动完成依赖仓库的下载与构建流程：

```shell
python build.py
```

### 2.3 安装

#### 2.3.1 准备 run 包

whl 包将生成于 output 目录下，执行以下命令确保其具备可执行权限：

```shell
cd output
chmod +x mindstudio_kpp-XXX.whl
```

#### 2.3.2 安装

将 whl 包拷贝到运行环境中（本机安装无需拷贝），执行如下安装操作：

```shell
pip install mindstudio_kpp-xxxxx.whl
```

#### 2.3.3 安装后配置

当前CANN包中已集成mskpp。在激活CANN环境，即可在自己的python脚本中使用mskpp

```shell
source ~/Ascend/cann/set_env.sh
python
>>> import mskpp
>>> ...
```

### 2.4 卸载

可通过如下命令卸载：

```shell
pip uninstall mindstudio_kpp-xxxxx.whl 
```

### 2.5 升级

如需使用whl包替换运行环境原有已安装的whl包，执行如下安装操作：

```shell
pip install mindstudio_kpp-xxxxx.whl --force-reinstall
```

安装过程中，若提示是否替换原有安装包：
输入"y"，则安装包会自动完成升级操作。
