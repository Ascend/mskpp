# MindStudio Kernel Performance Prediction 安装指南

<br>

## 1. 二进制安装

MindStudio工具链是集成到CANN包中发布的，可通过以下方式完成安装：

### 方式一：依据 CANN 官方文档安装  

请参考<a href="https://www.hiascend.com/document/detail/zh/canncommercial/850/softwareinst" target="_blank">《CANN安装官方文档》</a>，
按文档逐步安装和配置。

### 方式二：使用CANN官方容器镜像   

请访问<a href="https://www.hiascend.com/developer/ascendhub/detail/17da20d1c2b6493cb38765adeba85884" target="_blank">《CANN官方镜像仓库》</a>，
按照仓库中的指引完成镜像拉取及容器启动。

<br>  

## 2. 源码安装

如需使用最新代码的功能，或对源码进行修改以增强功能，可下载本仓库代码，自行编译、打包工具并完成安装。

### 2.1 环境准备

请按照以下文档进行环境配置：[《算子工具开发环境安装指导》](https://gitcode.com/Ascend/msot/blob/master/docs/zh/common/dev_env_setup.md)。

要求构建环境中安装`python3.9`或以上版本才能正常运行。

mskpp需要依赖其他python库。通过`pip install -r requirement.txt`一键式安装依赖库。
依赖库列表如下

```text
plotly>=5.11.0
```

### 2.2 执行编译打包

通过一键式脚本自动完成依赖仓库的下载与构建流程：

```shell
python build.py
```

### 2.3 安装与卸载

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

#### 2.3.4 卸载

可通过如下命令卸载：

```shell
pip uninstall mskpp-xxxxx.whl 
```

#### 2.3.5 升级

如需使用whl包替换运行环境原有已安装的whl包，执行如下安装操作：

```shell
pip install mindstudio_kpp-xxxxx.whl --force-reinstall
```

安装过程中，若提示是否替换原有安装包：
输入"y"，则安装包会自动完成升级操作。
