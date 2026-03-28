# msKPP 算子建模工具快速入门

<br>

## 1. 概述

msKPP 工具用于算子开发前的性能建模设计，开发者基于其 DSL（Domain-Specific Language，领域特定语言），以算子的数学逻辑为输入，编写算子表达式，即可在秒级内获得性能预测结果。该建模仅依赖输入/输出规模，无需执行真实计算，可高效验证算子实现方案。  
本文档基于入门教程中开发的简易加法算子，演示 msKPP 工具的核心功能，帮助初学者直观感受 msKPP 在算子开发过程中的高效与便捷。

### 1.1 建议

本章节以您已完成<a href="https://gitcode.com/Ascend/msot/blob/master/docs/zh/quick_start/op_tool_quick_start.md" target="_blank">《昇腾算子开发工具链快速入门》</a>的全流程操作为前提；若尚未体验，建议先完成该指南以获得更佳的学习效果。

### 1.2 环境准备

请严格按照<a href="https://gitcode.com/Ascend/msot/blob/master/docs/zh/quick_start/installation_guide.md" target="_blank">《昇腾 AI 算子开发工具链学习环境安装指南》</a>完成环境安装与工作区配置。
即使您已具备类似环境，也需按该指南重新执行一遍，以确保所有依赖组件、环境变量等完整一致。

<br>

## 2. 操作步骤

### 2.1 【环境】运行环境预检

#### 2.1.1 确认 Python 依赖包已安装

执行以下命令，若输出"All is OK"，则表明所需 Python 包及其版本均符合要求：

```shell
python3 -c "import numpy, sympy, scipy, attrs, psutil, decorator; from packaging import version; assert version.parse(numpy.__version__) <= version.parse('1.26.4'); print('All is OK')"
```

若报错，请参照[第 1.2 节](#12-环境准备)进行正确安装。

### 2.2 算子建模设计（msKPP）

在算子算法设计阶段，借助 msKPP 工具可在秒级时间内获得性能建模结果，无需硬件即可预估性能，快速验证实现方案的可行性。建议先跟随操作步骤体验效果，原理部分可稍后阅读：

>[!NOTE] 说明   
> **知识点：msKPP 工具原理**   
> msKPP 并非传统可执行程序，而是一套专用于昇腾的 Python 类库。用户需导入（import）相关模块，编写并执行 Python 脚本，生成性能分析结果文件以完成建模。其内部原理是：预先采集真实环境中各类指令操作的性能数据，再基于用户定义的算子执行流程，对各种性能开销进行建模与估算。

#### 2.2.1 编写 Python 建模脚本

##### 2.2.1.1 创建子工作区目录

```shell
rm -rf ~/ot_demo/workspace/mskpp && mkdir -p ~/ot_demo/workspace/mskpp && cd ~/ot_demo/workspace/mskpp
```

##### 2.2.1.2 开发 Python 脚本   

>[!NOTE] 说明  
>**知识点（可选阅读）：msKPP 的 DSL 语言方案（Domain-Specific Language，领域特定语言）**   
>这套类库及接口是专为昇腾性能建模而设计的"方言"，需经过专门学习方可掌握，无法仅凭通用 Python 语法直接编写，但用法较简单，稍加学习即可应用。  
>常规开发流程：需先导入 Tensor、Chip 以及算子实现所必需的指令（例如 vadd），通过 with 语句进入算子实现的上下文，再创建 Tensor 以执行具体操作。
>样例脚本中已经做了详细的注释，其他指令接口说明请参考[《msKPP 工具接口说明》](../api_reference/mskpp_api_reference.md)。

请创建文件 mskpp_demo.py，内容如下：

```python
import os
from mskpp import vadd, Tensor, Chip

def my_vadd(gm_x, gm_y, gm_z):
    # 向量Add的基本数据通路：
    # 被加数x: GM-UB
    # 加数y: GM-UB
    # 结果向量z: UB-GM

    # 定义和分配UB上的变量
    x = Tensor("UB")
    y = Tensor("UB")
    z = Tensor("UB")

    # 将GM上的数据移动到UB对应的内存空间上
    x.load(gm_x)
    y.load(gm_y)

    # 当前数据已加载到UB上，调用指令进行计算，结果保存在UB上
    out = vadd(x, y, z)()

    # 将UB上的数据移动到GM变量gm_z的地址空间上
    # vadd的返回值out是一个元组类型，通过下标取第0个元素
    gm_z.load(out[0])

if __name__ == '__main__':
    with Chip("xxx") as chip:  # 格式为Ascendxxxyy，其中xxx为用户实际使用的芯片SoC类型
        chip.enable_trace()  # 使能算子模拟流水图的功能，生成trace.json文件
        chip.enable_metrics() # 使能单指令及分PIPE的流水信息，生成Instruction_statistic.csv和Pipe_statistic.csv文件

        # 应用算子进行AI Core计算
        in_x = Tensor("GM", "FP16", [32, 48], format="ND")
        in_y = Tensor("GM", "FP16", [32, 48], format="ND")
        in_z = Tensor("GM", "FP16", [32, 48], format="ND")
        my_vadd(in_x, in_y, in_z)
```

##### 2.2.1.3 修改如上代码中的芯片类型   

参考<a href="https://gitcode.com/Ascend/msot/blob/master/docs/zh/quick_start/get_chip_soc_type.md" target="_blank">《芯片 SoC 类型获取方法》</a>获取芯片类型，将 `with Chip("xxx") as chip` 中的 xxx 替换为查询到的芯片类型。

#### 2.2.2 执行性能建模

执行 Python 脚本开始性能建模，若执行成功，将自动在当前目录下生成 `MSKPP{timestamp}` 结果目录：

```shell
python3 mskpp_demo.py
```

#### 2.2.3 查看建模结果

生成如下结果目录：

```text
MSKPP{timestamp}/
├── Instruction_statistic.csv
├── Pipe_statistic.csv
└── trace.json
```

以 Instruction_statistic.csv 为例，其内容如下：

| Instruction  | Duration(us) | Cycle | Size(B) | Ops  |
|:--------------:|:--------------:|:-------:|:---------:|:------:|
| MOV-GM_TO_UB |    0.3081    |  570  |  6144   |  -   |
|     VADD     |    0.0135    |  25   |    -    | 1536 |
| MOV-UB_TO_GM |    0.4254    |  787  |  3072   |  -   |

由上述内容可见，MOV-UB_TO_GM（从 UB 搬移到 GM）的耗时（Duration）最长，指令周期数（Cycle）也最多，是性能优化中需重点关注的关键路径。在实际开发中，如果发现此类内存搬运耗时占比过高，应优先考虑优化数据复用（Tiling）策略，或使用更高效的搬运指令。
