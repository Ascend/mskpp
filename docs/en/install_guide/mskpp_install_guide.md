# MindStudio Kernel Performance Prediction Installation Guide

This document describes how to install the msKPP tool: **using the CANN package** and **building from source**.

## Binary Installation

The MindStudio toolchain is integrated into the CANN package for release. You can install it in either of the following ways.

### Method 1: Install the software according to the CANN official document

For details, see <a href="https://www.hiascend.com/document/detail/zh/canncommercial/850/softwareinst" target="_blank">CANN Installation Guide</a>.
Perform the installation and configuration step by step according to the document.

### Method 2: Use the official CANN container image

Visit <a href="https://www.hiascend.com/developer/ascendhub/detail/17da20d1c2b6493cb38765adeba85884" target="_blank">CANN official image repository</a>.
Pull the image and start the container according to the instructions in the repository.

<br>  

## Installation from Source Code

To use the functions of the latest code or modify the source code to enhance functions, you can download the code from this repository, build and package the tool, and install it.

### Environment Setup

Set up the environment by referring to the [Operator Tool Development Environment Setup Guide](https://gitcode.com/Ascend/msot/blob/master/docs/en/common/dev_env_setup.md).

Python 3.9 or later must be installed in the build environment.

msKPP depends on other Python libraries. You can run the `pip install -r requirement.txt` command to install the dependency libraries in one-click mode.
The dependency list is as follows:

```text
plotly>=5.11.0
```

### Building and Packaging

Run the one-click script to automatically download and build the dependency repository:

```shell
python build.py
```

### Installation and Uninstallation

#### Preparing the .run Package

The .whl package is generated in the `output` directory. Run the following commands to ensure that the .run package has the execute permission:

```shell
cd output
chmod +x mindstudio_kpp-XXX.whl
```

#### Installation

Copy the .whl package to the operating environment (not required for local installation) and run the following command to perform the installation:

```shell
pip install mindstudio_kpp-xxxxx.whl
```

#### Post-installation Configuration

The current CANN package has integrated msKPP. After activating the CANN environment, you can use msKPP in your Python script.

```shell
source ~/Ascend/cann/set_env.sh
python
>>> import mskpp
>>> ...
```

#### Uninstallation

You can run the following command to uninstall the tool:

```shell
pip uninstall mskpp-xxxxx.whl 
```

#### Upgrade

To replace the installed .whl package with another .whl package, run the following command:

```shell
pip install mindstudio_kpp-xxxxx.whl --force-reinstall
```

During the installation, if the system asks you whether to replace the original installation package,
enter `y`. The installation package will be automatically upgraded.
