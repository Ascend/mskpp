# MindStudio Kernel Performance Prediction 安装指南

<br>

## 1. 安装说明

msKPP工具的安装方式包括：

- 使用CANN包安装：msKPP工具完整功能已集成在CANN包中，请参考《[CANN 快速安装](https://www.hiascend.com/cann/download)》安装昇腾NPU驱动和CANN软件（包含Toolkit和ops包），并配置环境变量。
- 源码编译安装：如需使用最新代码的功能，或对源码进行修改以增强功能，可下载本仓库代码，自行编译、打包工具并完成安装，具体请参见[源码编译安装](#2-源码编译安装)。

## 2. 源码编译安装

如需使用最新代码的功能，或对源码进行修改以增强功能，可下载本仓库代码，自行编译、打包工具并完成安装。

### 2.1 环境准备

请按照以下文档进行环境配置：《[算子工具开发环境安装指导](https://gitcode.com/Ascend/msot/blob/master/docs/zh/common/dev_env_setup.md)》。

要求构建环境中安装`python3.9`及以上版本才能正常运行。

- 克隆本仓库

    ```sh
    git clone https://gitcode.com/Ascend/mskpp.git
    ```

- mskpp需要依赖其他python库。通过如下命令一键式安装依赖库。

    ```sh
    cd mskpp
    pip install -r requirement.txt
    ```

    依赖库列表如下：`plotly>=5.11.0`。

### 2.2 执行编译打包

通过一键式脚本自动完成依赖仓库的下载与构建流程：

```shell
python build.py
```

### 2.3 安装

#### 2.3.1 安装

将 whl 包拷贝到运行环境中（本机安装无需拷贝），执行如下安装操作：

```shell
pip install mindstudio_kpp-xxxxx.whl
```

#### 2.3.2 安装后配置

当前CANN包中已集成msKPP工具。在激活CANN环境后，即可在自己的python脚本中使用msKPP工具。

```shell
source ~/Ascend/ascend-toolkit/set_env.sh
python
>>> import mskpp
>>> ...
```

### 2.4 卸载

可通过如下命令卸载：

```shell
pip uninstall mindstudio-kpp
```

### 2.5 升级

如需使用whl包替换运行环境原有已安装的whl包，执行如下安装操作：

```shell
pip install mindstudio_kpp-xxxxx.whl --force-reinstall
```
