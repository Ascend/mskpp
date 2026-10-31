# msKPP Installation Guide

<br>

## 1. Installation Description

This tool has been integrated into CANN. If CANN has been installed and this tool does not need to be updated, you can directly use it without following the instructions in this document.

If CANN has not been installed in your environment, install the Ascend NPU driver and CANN software (including the Toolkit and ops) by referring to [CANN Quick Installation](https://www.hiascend.com/cann/download), and configure environment variables.

If you need to upgrade this tool separately or use the latest version, you can install it in any of the following ways: [Online Installation](#21-online-installation), [Offline Installation](#22-offline-installation), and [Source Installation](#23-source-installation).

## 2. Installation Methods

### 2.1 Online Installation

If your device has Internet access, you can run a single command to automatically download and install the tool. Visit the [Ascend community](https://www.hiascend.com/developer/software/mindstudio/download), select the target CANN version, and choose "Online" installation method. The system will guide you through the subsequent operations.

### 2.2 Offline Installation

For devices that are not connected to the Internet, such as those on an enterprise intranet, download the complete offline installation package on a device that has Internet access and then transfer the package to the target device for installation. Visit the [Ascend community](https://www.hiascend.com/developer/software/mindstudio/download), select the target CANN version, and choose "Offline" installation method. The system will guide you through the subsequent operations.

### 2.3 Source Installation

To use the functions of the latest code or modify the source code to enhance functions, you can download the code from this repository, build and package the tool, and install it.

#### 2.3.1 Preparing the Environment

All source code compilation uses the standard MindStudio build environment.

- For daily development or when you use a released image, refer to the [MindStudio Tool Development Environment Installation Guide](https://gitcode.com/Ascend/msot/blob/master/docs/en/common/dev_env_setup.md).
- If you need to reproduce the environment from a base operating system, perform source code build verification or unit test verification, you must refer to the [MindStudio Unified Build Image Creation Guide](https://gitcode.com/Ascend/msot/blob/master/docs/en/common/docker_image_build_guide.md) to build the environment image on site from the openEuler base image.

The source code compilation and unit test commands later in this document are all run in the container of the specified image or of the environment image built on site. The CANN software package version, GCC version, and Python version are subject to the *Unified Build Image Creation Guide*, and this repository does not maintain them separately.

After the image is built, you must use the `ctr_in.py` command provided in Chapter 7 of the *Unified Build Image Creation Guide* to start and enter the container in an interactive terminal. Do not use a plain `docker run` to create a container, and do not use `docker exec <container_name> bash -c '<command>'` to replace the interactive environment. Otherwise, the initialization of the Python, GCC, and CANN environments may be skipped.

After you enter the interactive container shell opened by `ctr_in.py`, run the following command to clone this repository:

```bash
cd ~
git clone https://gitcode.com/Ascend/mskpp.git
```

#### 2.3.2 Compilation

Stay in the same interactive container shell opened by `ctr_in.py`, and run the following command in the repository root directory to automatically download dependencies and build:

```bash
cd ~/mskpp
python3 build.py
```

After the build succeeds, the installation package is generated in the `artifacts/` directory.

#### 2.3.3 Unit Tests (Optional)

This step is not required for installation. If you need to verify the basic functions of the code, you can run the unit tests:

```bash
cd ~/mskpp
python3 build.py test
```

If the return code of the command is 0 and no test case fails, the unit tests pass.

#### 2.3.4 Installation

##### 2.3.4.1 Installation Package

Copy the `.whl` package to the operating environment (not required for local installation) and run the following command to perform the installation:

```shell
cd ~/mskpp/artifacts
pip install mindstudio_kpp-xxxxx.whl
```

If information similar to the following is displayed, the installation is successful:

```text
Successfully installed mindstudio-kpp-xxxxx
```

##### 2.3.4.2 Post-installation Configuration

The msKPP tool has been integrated into the CANN package. After the CANN environment is activated, you can use the msKPP tool in your Python script.

```shell
source /usr/local/Ascend/ascend-toolkit/set_env.sh
python
>>> import mskpp
>>> ...
```

## 3. Verifying Installation

After installation, run the following command to verify whether the tool was installed successfully:

```shell
python3 -c "import mskpp; print('All is OK')"
```

If no error is reported and the output displays `All is OK`, the installation is successful.

## 4. Uninstallation

To uninstall the tool, perform the following steps:

1. Download the script.

   ```bash
   curl -O https://inst.obs.cn-north-4.myhuaweicloud.com/26.2.0/ms_install.py
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

You can run the `pip3 show mindstudio-kpp` command to view the version information of the current environment, and then select the version to upgrade to. When upgrading the version, pay attention to the version compatibility relationships. Refer to [Version Notes](https://gitcode.com/Ascend/release-management/blob/master/MindStudio/master/release_notes.md).
