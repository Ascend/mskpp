# MindStudio Kernel Performance Prediction Installation Guide

<br>

## 1. Installation Description

This tool has been integrated into CANN. If CANN has been installed and this tool does not need to be updated, you can directly use it without following the instructions in this document.

If CANN has not been installed in your environment, install the Ascend NPU driver and CANN software (including the Toolkit and ops) by referring to [CANN Quick Installation](https://www.hiascend.com/cann/download), and configure environment variables.

If you need to upgrade this tool separately or use the latest version, you can install it in any of the following ways: [Online Installation](#21-online-installation), [Offline Installation](#22-offline-installation), and [Source Installation](#23-source-installation).

## 2. Installation Methods

### 2.1 Online Installation

If your device has Internet access, you can run a single command to automatically download and install the tool. Visit the [Ascend community](https://www.hiascend.com/en/developer/software/mindstudio/download), select the target CANN version, and choose "Online" installation method. The system will guide you through the subsequent operations.

### 2.2 Offline Installation

For devices that are not connected to the Internet, such as those on an enterprise intranet, download the complete offline installation package on a device that has Internet access and then transfer the package to the target device for installation. Visit the [Ascend community](https://www.hiascend.com/en/developer/software/mindstudio/download), select the target CANN version, and choose "Offline" installation method. The system will guide you through the subsequent operations.

### 2.3 Source Installation

To use the functions of the latest code or modify the source code to enhance functions, you can download the code from this repository, build and package the tool, and install it.

#### 2.3.1 Preparing the Environment

Configure the environment by referring to [Operator Tool Development Environment Setup Guide](https://gitcode.com/Ascend/msot/blob/26.0.0/docs/en/common/dev_env_setup.md).

Python 3.9 or later must be installed in the build environment.

- Clone this repository.

    ```sh
    git clone https://gitcode.com/Ascend/mskpp.git -b 26.0.0
    ```

- msKPP depends on other Python libraries. Run the following command to install the dependency libraries in one-click mode:

    ```sh
    cd mskpp
    pip install -r requirement.txt
    ```

    The dependency library is `plotly>=5.11.0`.

#### 2.3.2 Building and Packaging

Run the one-click script to automatically download and build the dependency repository:

```shell
python build.py
```

#### 2.3.3 Installation

##### 2.3.3.1 Installation Package

Copy the .whl package to the operating environment (not required for local installation) and run the following command to perform the installation:

```shell
pip install mindstudio_kpp-xxxxx.whl
```

If information similar to the following is displayed, the installation is successful:

```text
Successfully installed mindstudio-kpp-xxxxx
```

##### 2.3.3.2 Post-installation Configuration

The msKPP tool has been integrated into the CANN package. After the CANN environment is activated, you can use the msKPP tool in your Python script.

```shell
source /usr/local/Ascend/ascend-toolkit/set_env.sh
python
>>> import mskpp
>>> ...
```

## 3. Verify Installation

After installation, run the following command to verify whether the tool was installed successfully:

```shell
python3 -c "import mskpp; print('All is OK')"
```

If no error is reported and the output display `All is OK`, the installation is successful.

## 4. Uninstallation

To uninstall the tool, perform the following steps:

1. Download the script.

   ```bash
   curl -O https://inst.obs.cn-north-4.myhuaweicloud.com/26.0.0/ms_install.py
   ```

   > [!NOTE]
   >
   > - Internet access is required to download the script. If your target environment is offline or does not allow Internet access, download the script on an Internet-connected device first, then copy it to the target device.
   > - If the command does not respond, or you encounter connection failures, SSL certificate errors, or other issues, refer to the [FAQ](https://www.hiascend.com/developer/blog/details/02176213671719317003).

2. Uninstall the tool.

   ```bash
   python ms_install.py uninstall {tools_name}
   ```

   Replace `{tools_name}` with the name of the tool to be uninstalled. You can run the `python ms_install.py help` command to query the tool name, which is displayed under the `Available Tools` field in the command output.

   If the uninstallation is successful, the following information is displayed:

   ```text
   Successfully uninstalled 1 tool ({tools_name})
   ```

## 5. Upgrade

Upgrades follow the "uninstall first, then install" process. Simply run the installation command. The tool will automatically remove the previous version and guide you through the upgrade process.
