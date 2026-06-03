# Development Environment Setup, Compilation, and UT Methods for MindStudio Kernel Performance Prediction

<br>

## 1. Background Knowledge Required

For details about the code framework and core process, see the [msKPP Architecture Design Specifications](./architecture.md).

## 2. Development Environment Setup

- For hardware environment requirements, see [Ascend Product Models](https://www.hiascend.com/document/detail/zh/AscendFAQ/ProduTech/productform/hardwaredesc_0001.html).

- Set up the environment by referring to the [Operator Tool Development Environment Setup Guide](https://gitcode.com/Ascend/msot/blob/master/docs/en/common/dev_env_setup.md).

- Python 3.9 or later must be installed in the build environment.

- msKPP depends on other Python libraries. You can run the `pip install -r requirement.txt` command to install the dependency libraries in one-click mode.
- `GCC version > 7.4.0` 
- `3.20.2 <= CMAKE version <= 3.31.10`

## 3. Building and Packaging

There are two methods, each with its own advantages and disadvantages:

| Method| Application Scenario| Advantages| Disadvantages|
|------|---------|------|------|
| One-click script| Initial build and CI/CD pipeline| Zero configuration, one-step setup| Steps cannot be executed independently.|
| Step-by-step script| Routine development and incremental build| Flexibility and efficiency| Multiple steps are required.|

### 3.1 Method 1: One-click Script

```shell
python build.py
```

### 3.2 Method 2: Step-by-Step Script

#### 3.2.1 Building and Packaging

```shell
mkdir build
cd build
cmake ..
make -j$(nproc) install # -j indicates the number of parallel build jobs, which can be specified as required. If nproc is unavailable, manually enter a number (for example, -j8).
```

##### 3.2.1.2 Build Result Description

The build result is generated in the `output` directory:

```text
output/
|-- include                                              # API header file
|-- lib                                                  # Static library
|-- lib64                                                # Dynamic library
|-- mindstudio_kpp-XXX-py3-none-manylinux_2_31_XXX.whl   # Installation package
```

#### 3.2.3 Cleanup/Rebuild

Delete the build directory and perform operations in [Section 3.2.1](#321-building-and-packaging) again.  

```shell
rm -rf build
```

## 4. Running UT

### 4.1 One-click script

The Python UT depends on the pytest and coverage tools, which can be installed by running `pip install coverage pytest`.

```shell
python build.py test
```

If the number of executed test cases is the same as the number of passed test cases, the test is successful. The output is similar to the following:

```text
[==========] 37 tests from 6 test cases ran. (616 ms total)
[  PASSED  ] 37 tests.
```

### 4.2 Cleanup/Rebuild

Delete the build directory and perform operations in [Section 4.1](#41-one-click-script) again.  

```shell
rm -rf build_ut  
```
