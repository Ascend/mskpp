# msKPP Development Guide

<br>

This document describes how to set up the development environment for MindStudio Kernel Performance Prediction (msKPP), build the project, and run UT unit tests.

## 1. Prerequisites

### 1.1 Prerequisite Knowledge

Before starting development, read [msKPP Architecture Design Specifications](./architecture.md) to learn about the code framework and core processes.

### 1.2 Environment Preparation

Follow [msKPP Installation Guide — Source Installation](../install_guide/mskpp_install_guide.md#231-preparing-the-environment) to set up the build and test environment.

> **Note:** The environment image build method and the supporting software versions are maintained by the *MindStudio Unified Build Image Creation Guide* and are not redefined in this repository.

## 2. Build

Run the following in the project root directory:

```bash
python3 build.py
```

### 2.1 Build Artifacts

After a successful build, the output is generated in the `artifacts` directory.

### 2.2 Build Cleanup

To perform a full rebuild, delete the build directory and run the preceding steps again:

```bash
rm -rf build
```

## 3. Unit Tests

### 3.1 Running Tests

```bash
python3 build.py test
```

When all tests pass, the output is similar to the following example:

```text
[==========] 37 tests from 6 test cases ran. (616 ms total)
[  PASSED  ] 37 tests.
```

> **Pass criteria:** The tests pass when the number of `ran` test cases matches the number of `PASSED` test cases. If any `FAILED` test cases exist, locate the cause of the failure from the logs.

### 3.2 Cleaning the Test Environment

Delete the UT build directory and run the tests again:

```bash
rm -rf build_ut
```
