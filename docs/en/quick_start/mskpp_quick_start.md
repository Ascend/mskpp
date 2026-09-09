# msKPP Quick Start

<br>

## 1. Overview

The msKPP tool is used for performance modeling design before operator development. Developers can compile operator expressions based on the domain-specific language (DSL) and the mathematical logic of operators, and obtain performance prediction results within seconds. This modeling depends only on the input/output scale and does not require actual computation, allowing for efficient verification of operator implementation solutions. This document demonstrates the core functions of msKPP based on the simple addition operator developed in the introductory tutorial. It helps beginners intuitively experience the efficiency and convenience the tool brings to the operator development process.

This section assumes that you have completed all the operations in <a href="https://gitcode.com/Ascend/msot/blob/master/docs/en/quick_start/op_tool_quick_start.md" target="_blank">Quick Start of the Operator Development Toolchain</a>. If you have not, you are advised to complete this guide first to obtain a better learning effect.

## 2. Procedure

### 2.1 Essential Environment Preparation (Mandatory Prerequisite ⚠️)

🛑 **This section is a mandatory prerequisite step! Skipping it will cause many failures in subsequent operations.**  
This tutorial **only supports** the standard CANN container environment and is not compatible with bare-metal servers, virtual machines, or other non-standard container deployments.

#### 2.1.1 Installing the CANN Container Environment

✅ **Strictly follow the guide to complete the environment installation:**  
👉 **<a href="https://gitcode.com/Ascend/msot/blob/master/docs/en/quick_start/installation_guide.md" target="_blank">Ascend AI Operator Development Toolchain Learning Environment Installation Guide</a>**

> ⏱️ **Estimated time in a network-reachable environment: about 3 minutes**  
> After the installation, you will obtain a standard container environment preinstalled with all operator tools, sample code, and dependent libraries.

#### 2.1.2 Running the Environment Self-Check Script (Must Pass!)

Before the hands-on experience, **copy the entire script in the following code block**, paste it into the terminal, and run it. You can continue only when all output displays [PASS]:

```bash
# 1. Container environment check
[ -f /.dockerenv ] && [ -n "$ASCEND_HOME_PATH" ] && [ -n "$ATB_HOME_PATH" ] && echo -e "\033[32m[PASS] CANN container environment OK \033[0m" || echo -e "\033[31m[FAIL] Non-standard container or not in a container!\033[0m"
# 2. Sample code repository check
[ -d ~/ot_demo/msot/example/quick_start ] && echo -e "\033[32m[PASS] Sample code repository OK\033[0m" || echo -e "\033[31m[FAIL] Code repository missing\033[0m"
```

### 2.2 Operator Modeling Design (msKPP)

During operator algorithm design, the msKPP tool can be used to obtain performance modeling results within seconds. It allows for performance estimation without hardware and quickly verifies the feasibility of implementation solutions. You are advised to follow the operations first to experience the effect. You can read the principles later.

> [!NOTE]
> 
> **Knowledge point: principles of the msKPP tool**  
> msKPP is not an executable program, but a Python class library dedicated to Ascend. You need to import related modules, compile and execute Python scripts, and generate profiling result files to complete modeling. The internal principle involves pre-collecting profile data of various instruction operations in real environments, then modeling and estimating various performance overheads based on the user-defined operator execution flow.

#### 2.2.1 Compiling a Python Modeling Script

##### 2.2.1.1 Creating a Workspace Subdirectory

```shell
rm -rf ~/ot_demo/workspace/mskpp && mkdir -p ~/ot_demo/workspace/mskpp && cd ~/ot_demo/workspace/mskpp
```

##### 2.2.1.2 Developing a Python Script  

> [!NOTE]
> 
> **(Optional) Knowledge point: the msKPP DSL solution**  
> This class library and APIs are designed as a "dialect" specifically for Ascend performance modeling. Mastery of this DSL requires dedicated learning, as it is not directly writable with general Python syntax. However, the usage model is relatively straightforward and can be picked up quickly with a small amount of guided effort. 
> Typical development process: Import the necessary instructions (such as `vadd`) for tensors, chips, and operator implementation. Use the `with` statement to enter the context of operator implementation, and then create tensors to perform specific operations.
> The sample script contains detailed comments. For details about other instruction APIs, see [msKPP API Reference](../api_reference/mskpp_api_reference.md).

Create the `mskpp_demo.py` file with the following content:

```python
import os
from mskpp import vadd, Tensor, Chip

def my_vadd(gm_x, gm_y, gm_z):
    # Basic data path of vector Add:
    # Augend x: GM-UB
    # Addend y: GM-UB
    # Result vector z: UB-GM

    # Define and allocate variables on the UB
    x = Tensor("UB")
    y = Tensor("UB")
    z = Tensor("UB")

    # Move the data on the GM to the memory space corresponding to the UB
    x.load(gm_x)
    y.load(gm_y)

    # The current data has been loaded to the UB. Call calculation instruction, and save the result to the UB
    out = vadd(x, y, z)()

    # Move the data on the UB to the address space of the GM variable gm_z
    # The return value out of vadd is a tuple. Use the index to obtain the 0th element
    gm_z.load(out[0])

if __name__ == '__main__':
    with Chip("xxx") as chip:  # xxx indicates the SoC type of the chip, for example, Ascendxxxyy
        chip.enable_trace() # Enable the operator simulation pipeline chart function to generate the trace.json file
        chip.enable_metrics() # Enable single instruction and pipeline information to generate the Instruction_statistic.csv and Pipe_statistic.csv files

        # Use the operator for AI Core computation
        in_x = Tensor("GM", "FP16", [32, 48], format="ND")
        in_y = Tensor("GM", "FP16", [32, 48], format="ND")
        in_z = Tensor("GM", "FP16", [32, 48], format="ND")
        my_vadd(in_x, in_y, in_z)
```

##### 2.2.1.3 Modifying the Processor Type in the Preceding Code

Run the `python3 -c "import acl; print(acl.get_soc_name())"` command to obtain the SoC type of the chip. Replace `xxx` in `with Chip("xxx") as chip` with the obtained result.

#### 2.2.2 Executing Performance Modeling

Run the Python script to start performance modeling. If the execution is successful, the `MSKPP{timestamp}` result directory is automatically generated in the current directory.

```shell
python3 mskpp_demo.py
```

#### 2.2.3 Viewing the Modeling Result

The following result directories are generated:

```text
MSKPP{timestamp}/
├── instruction_cycle_consumption.html
├── Instruction_statistic.csv
├── Pipe_statistic.csv
└── trace.json
```

The following uses `Instruction_statistic.csv` as an example. The content is as follows:

| Instruction  | Duration(us) | Cycle | Size(Byte) | Ops  |
|:--------------:|:--------------:|:-------:|:---------:|:------:|
| MOV-GM_TO_UB |    0.3081    |  570  |  6144   |  -   |
|     VADD     |    0.0135    |  25   |    -    | 1536 |
| MOV-UB_TO_GM |    0.4254    |  787  |  3072   |  -   |

As shown in the preceding table, `MOV-UB_TO_GM` (transferring data from the UB to the GM) takes the longest duration and has the most instruction cycles, making it the critical path that requires primary attention in performance tuning. In practice, if such memory transfer operations are observed to dominate execution time, developers should prioritize optimizing the data tiling policy, or alternatively, employ more efficient transfer instructions.
