# **MindStudio Kernel Performance Prediction对外接口使用说明**

## 接口列表

msKPP工具分为基础功能接口和指令接口两种接口类型。基础功能接口用于模拟算子计算中芯片平台、基础数据等。指令接口用于模拟特定的算子指令操作，包括Vector类计算指令和Cube类计算指令。

**表 1**  msKPP工具接口列表

|接口名称|接口简介|
|--|--|
|[基础功能接口](#基础功能接口)|-|
|[Chip](#Chip)|创建性能建模的芯片平台，初始化芯片各项性能数据。|
|[Core](#Core)|模拟芯片内部的AI Core。|
|[Tensor](#Tensor)|算子执行基础数据类型。|
|[Tensor.load](#Tensor.load)|数据搬运接口，对数据在不同单元搬运进行建模。|
|[同步类指令接口](#同步类指令接口)|-|
|[set_flag](#set_flag)|核内PIPE间同步的指令接口，与wait_flag配套使用。|
|[wait_flag](#wait_flag)|核内PIPE间同步的指令接口，与set_flag配套使用。|
|[指令接口](#指令接口)|-|
|[mmad](#mmad)|对Cube类指令的mmad性能建模接口。|
|[vadd](#vadd)|对Vector类指令的vadd性能建模接口。|
|[vbrcb](#vbrcb)|对Vector类指令的vbrcb性能建模接口。|
|[vconv](#vconv)|对Vector类指令的vconv性能建模接口。|
|[vconv_deq](#vconv_deq)|对Vector类指令的vconv_deq性能建模接口。|
|[vconv_vdeq](#vconv_vdeq)|对Vector类指令的vconv_vdeq性能建模接口。|
|[vector_dup](#vector_dup)|对Vector类指令的vector_dup性能建模接口。|
|[vexp](#vexp)|对Vector类指令的vexp性能建模接口。|
|[vln](#vln)|对Vector类指令的vln性能建模接口。|
|[vmax](#vmax)|对Vector类指令的vmax性能建模接口。|
|[vmul](#vmul)|对Vector类指令的vmul性能建模接口。|
|[vmuls](#vmuls)|对Vector类指令的vmuls性能建模接口。|
|[vsub](#vsub)|对Vector类指令的vsub性能建模接口。|
|[vdiv](#vdiv)|对Vector类指令的vdiv性能建模接口。|
|[vcadd](#vcadd)|对Vector类指令的vcadd性能建模接口。|
|[vabs](#vabs)|对Vector类指令的vabs性能建模接口。|
|[vaddrelu](#vaddrelu)|对Vector类指令的vaddrelu性能建模接口。|
|[vaddreluconv](#vaddreluconv)|对Vector类指令的vaddreluconv性能建模接口。|
|[vadds](#vadds)|对Vector类指令的vadds性能建模接口。|
|[vand](#vand)|对Vector类指令的vand性能建模接口。|
|[vaxpy](#vaxpy)|对Vector类指令的vaxpy性能建模接口。|
|[vbitsort](#vbitsort)|对Vector类指令的vbitsort性能建模接口。|
|[vcgadd](#vcgadd)|对Vector类指令的vcgadd性能建模接口。|
|[vcgmax](#vcgmax)|对Vector类指令的vcgmax性能建模接口。|
|[vcgmin](#vcgmin)|对Vector类指令的vcgmin性能建模接口。|
|[vcmax](#vcmax)|对Vector类指令的vcmax性能建模接口。|
|[vcmin](#vcmin)|对Vector类指令的vcmin性能建模接口。|
|[vcmp__xxx_](#vcmp__xxx_)|对Vector类指令的vcmp_xxx性能建模接口。|
|[vcmpv__xxx_](#vcmpv__xxx_)|对Vector类指令的vcmpv_xxx性能建模接口。|
|[vcmpvs__xxx_](#vcmpvs__xxx_)|对Vector类指令的vcmpvs_xxx性能建模接口。|
|[vcopy](#vcopy)|对Vector类指令的vcopy性能建模接口。|
|[vcpadd](#vcpadd)|对Vector类指令的vcpadd性能建模接口。|
|[vgather](#vgather)|对Vector类指令的vgather性能建模接口。|
|[vgatherb](#vgatherb)|对Vector类指令的vgatherb性能建模接口。|
|[vlrelu](#vlrelu)|对Vector类指令的vlrelu性能建模接口。|
|[vmadd](#vmadd)|对Vector类指令的vmadd性能建模接口。|
|[vmaddrelu](#vmaddrelu)|对Vector类指令的vmaddrelu性能建模接口。|
|[vmaxs](#vmaxs)|对Vector类指令的vmaxs性能建模接口。|
|[vmin](#vmin)|对Vector类指令的vmin性能建模接口。|
|[vmins](#vmins)|对Vector类指令的vmins性能建模接口。|
|[vmla](#vmla)|对Vector类指令的vmla性能建模接口。|
|[vmrgsort](#vmrgsort)|对Vector类指令的vmrgsort性能建模接口。|
|[vmulconv](#vmulconv)|对Vector类指令的vmulconv性能建模接口。|
|[vnot](#vnot)|对Vector类指令的vnot性能建模接口。|
|[vor](#vor)|对Vector类指令的vor性能建模接口。|
|[vrec](#vrec)|对Vector类指令的vrec性能建模接口。|
|[vreduce](#vreduce)|对Vector类指令的vreduce性能建模接口。|
|[vreducev2](#vreducev2)|对Vector类指令的vreducev2性能建模接口。|
|[vrelu](#vrelu)|对Vector类指令的vrelu性能建模接口。|
|[vrsqrt](#vrsqrt)|对Vector类指令的vrsqrt性能建模接口。|
|[vsel](#vsel)|对Vector类指令的vsel性能建模接口。|
|[vshl](#vshl)|对Vector类指令的vshl性能建模接口。|
|[vshr](#vshr)|对Vector类指令的vshr性能建模接口。|
|[vsqrt](#vsqrt)|对Vector类指令的vsqrt性能建模接口。|
|[vsubrelu](#vsubrelu)|对Vector类指令的vsubrelu性能建模接口。|
|[vsubreluconv](#vsubreluconv)|对Vector类指令的vsubreluconv性能建模接口。|
|[vtranspose](#vtranspose)|对Vector类指令的vtranspose性能建模接口。|

## 基础功能接口

### <h3 id="Chip">Chip</h3>

**功能说明**

处理器抽象，在with语句中实例化并用来明确针对某一昇腾AI处理器类型进行建模。

**接口原型**

```python
class Chip(name, debug_mode=False)
```

**参数说明**

|参数名|输入类型|说明|
|--|--|--|
|name|string|处理器名称。目前大部分数据基于Atlas A2 训练系列产品/Atlas A2 推理系列产品采集，使用**npu-smi info**可以查看当前设备昇腾AI处理器类型。|
|debug_mode|bool|是否启用调试模式，默认为False。开启debug模式后可查看未正确运行的指令，但不会生成任何输出件。<br>True：启用<br/>False：不启用|

**成员说明**

|成员名称|描述|
|--|--|
|chip.enable_trace()|使能算子模拟流水图的功能，生成流水图文件trace.json。|
|chip.enable_metrics()|使能单指令及分PIPE的流水信息，生成指令统计（Instruction_statistic.csv）、搬运流水统计（Pipe_statistic.csv）文件和指令占比饼图（instruction_cycle_consumption.html）。|
|chip.set_cache_hit_ratio(config)|用于使能手动调整L2Cache命中率，其中config = {"cache_hit_ratio": 0.6}，具体介绍请参见支持cache命中率建模章节。|
|chip.set_prof_summary_path("xxx/PipeUtilization.csv")|其中PipeUtilization.csv为msprof的结果示例，用于使能PIPE信息的理论值与msprof实测值比对。具体介绍请参见支持PIPE信息的理论值与msprof实测值比对章节。|
|chip.disable_instr_log()|使能后，抑制指令任务添加和调度结束后的日志打印。|

**约束说明**

需在with语句下将该类初始化。

**使用示例**

```python
from mskpp import Chip
# 如何查看当前设备昇腾处理器类型请参见以下说明
with Chip("Ascendxxxyy") as chip:    # Ascendxxxyy需替换为实际使用的处理器类型
    chip.enable_trace()   # 调用该函数即可使能算子模拟流水图的功能，生成流水图文件
    chip.enable_metrics()  # 调用该函数即可使能单指令及分PIPE的流水信息，生成搬运流水统计、指令信息统计和指令占比饼图
```

> [!NOTE] 说明  
> 非Atlas A3 训练系列产品/Atlas A3 推理系列产品：在安装昇腾AI处理器的服务器执行**npu-smi info**命令进行查询，获取**Chip Name**信息。实际配置值为AscendChip Name，例如**Chip Name**取值为xxxyy，实际配置值为Ascendxxxyy。当Ascendxxxyy为代码样例的路径时，需要配置为ascendxxxyy。

**返回值说明**

无

### <h3 id="Core">Core</h3>

**功能说明**

AI Core抽象，在with语句中实例化并用来明确针对某一AI Core类型进行建模。

**接口原型**

```python
class Core(core_type_name)
```

**参数说明**

|参数名|输入类型|说明|
|--|--|--|
|core_type_name|string|昇腾计算单元类型字符串，通常可以表示为AICx或AIVx，其中x为数字，即使用的AI Cube Core/ AI Vector Core的序号。仅支持A-Za-z0-9中的一个或多个字符。|

**约束说明**

需在with语句下将该类初始化。

**使用示例**

```python
from mskpp import Core
with Core("AIC0") as aic:
    # AI Cube Core 0上的算子计算逻辑相关代码
    ...
```

**返回值说明**

无

### <h3 id="Tensor">Tensor</h3>

**功能说明**

片上Tensor的抽象，可指定Tensor的内存位置、数据类型、大小及排布格式作为指令的数据依赖标识。

**接口原型**

```python
class Tensor(mem_type, dtype=None, size=None, format=None, is_inited=False)
```

**参数说明**

|参数名|输入类型|说明|
|--|--|--|
|mem_type|字符串|抽象Tensor所处的内存空间的位置，如GM、UB、L1、L0A、L0B、L0C、FB、BT等。|
|dtype|字符串|数据类型，如BOOL、UINT1、UINT2、UINT8、UINT16、UINT32、BF16、UINT64、INT4、INT8、INT16、INT32、INT64、FP16、FP32。|
|size|list|Tensor的shape。|
|format|字符串|数据排布格式，详细可参见《Ascend C算子开发指南》的“编程指南 > 概念原理和术语 > 神经网络和算子> 数据排布格式”数据排布格式章节。|
|is_inited|bool|控制Tensor类是否已就绪的开关，开启后，以该Tensor为输入的指令即可启动。|

**成员说明**

|成员名称|描述|
|--|--|
|tensor.set_valid()|使能当前tensor就绪，开启后，以该tensor为输入的指令即可立即启动。|
|tensor.set_invalid()|使当前tensor处于非就绪状态，关闭后，以该tensor为输入的指令不可立即启动。|
|tensor.is_valid()|用于获取当前的tensor就绪状态。|

**约束说明**

需通过创建一个shape为[1]且is_inited=True的Tensor进行标量创建。

**使用示例**

```python
from mskpp import Tensor, Core
gm_tmp= Tensor("GM", "FP16", [48, 16], format="ND")
with Core("AIV0") as aiv:  # AIV0上的相关计算逻辑
    ...
    gm_tmp.load(result, set_value=0)
with Core("AIC0") as aic:
    in_x = Tensor("GM", "FP16", [48, 16], format="ND")
    in_x.load(gm_tmp, expect_value=0) # AIC0上的相关计算逻辑 
    ...
```

**返回值说明**

无

### <h3 id="Tensor.load">Tensor.load</h3>

**功能说明**

所有的数据搬运指令在msKPP工具下都抽象为load方法，用户只需关心昇腾AI处理器中合理的搬运通路，无需考虑搬运指令中复杂的stride概念。

**接口原型**

```python
Tensor.load(tensor, repeat=1, set_value=-1, expect_value=-1)
```

**参数说明**

|参数名|输入类型|说明|
|--|--|--|
|tensor|变量|输入的其他tensor，其功能与接口中Tensor的定义一致。|
|repeat|int|该参数是对搬运指令repeat的模拟，通过输入该值可获取不同repeat值下搬运通路的带宽值，该带宽值用于计算搬运指令的耗时。非必选参数，默认值为1，建议值为[1,255]之间的整数。当输入的repeat值不满足要求时，系统将会抛出异常："input repeat = *xx* invalid."，其中*xx*为输入的异常repeat值。|
|set_value|int|设置此tensor数据被依赖的标识号，可以自行定义，需与expect_value配对使用。非必选参数，不输入则不会使能依赖关系。|
|expect_value|int|设置此tensor数据加载依赖数据的标识号，可以自行定义，需与set_value配对使用。非必选参数，不输入则不会使能依赖关系。|

**约束说明**

set_value和expect_value需配对使用，否则可能会造成流水阻塞。

repeat参数仅支持以下4条搬运通路：L1_TO_L0A、L1_TO_L0B、GM_TO_L0A和GM_TO_L0B。

**返回值说明**

无

## 同步类指令接口

### set_flag

**功能说明**

用于确保核内各PIPE间不同指令的同步，pipe_src先完成调度后，pipe_dst将解除阻塞状态。设置set_flag和wait_flag之后，[指令流水图介绍（以MindStudio Insight为例）](https://www.hiascend.com/document/detail/zh/mindstudio/82RC1/ODtools/Operatordevelopmenttools/atlasopdev_16_0087.html)将会更贴合用户的调用预期。

**接口原型**

```python
set_flag(pipe_src, pipe_dst, event_id)
```

**参数说明**

|参数名|输入/输出|说明|
|--|--|--|
|pipe_src|输入|源PIPE，在pipe_src调度后设置event_id。<br>输入格式为aicore_PIPE，例如："aic0_PIPE-MTE1"。其中aicore的取值范围参见基础功能接口Core，PIPE取值范围为"PIPE-MTE1"、"PIPE-MTE2"、 "PIPE-MTE3"、"PIPE-FIX"、"PIPE-M"、"PIPE-V"、 "PIPE-S"。不指定aicore时，可直接输入PIPE取值。<br/>数据类型：string。<br/>必选参数。|
|pipe_dst|输入|目的PIPE，在pipe_src调度之后，pipe_dst将会解除阻塞状态。<br/>输入格式为aicore_PIPE，例如："aic0_PIPE-MTE1"。其中aicore的取值范围参见基础功能接口Core，PIPE取值范围为"PIPE-MTE1"、"PIPE-MTE2"、 "PIPE-MTE3"、"PIPE-FIX"、"PIPE-M"、"PIPE-V"、 "PIPE-S"。不指定aicore时，可直接输入PIPE取值。<br/>数据类型：string。<br/>必选参数。|
|event_id|输入|同步指令之间依赖的唯一值。<br/>取值范围[0, 65535]。<br/>数据类型：int。<br/>必选参数。|

**约束说明**

- 在同一核内set_flag与wait_flag个数需匹配。
- 同核内不应出现重复的set_flag指令。
- 同一核内，当set_flag和wait_flag内的pipe_src和pipe_dst相同时，event_id也应保持唯一。

**使用示例**

```python
from mskpp import Tensor, Chip, set_flag, wait_flag
with Chip("Ascendxxyy") as chip:
    gm_weight = Tensor("GM", "FP16", [128, 256], format="ND")
    l1_weight = Tensor("L1", "FP16", [128, 256], format="ND")
    for conv_idx in range(4):  # L0A数据加载前，GM分批加载到L1上
        gm_weight_part = gm_weight[:, 64]
        l1_weight_part = l1_weight[:, 64]
        l1_weight_part.load(gm_weight_part)
        if conv_idx == 3:
            set_flag("PIPE-MTE2", "PIPE-MTE1", 1)  # 当完成MTE2，才可以执行MTE1
    x = Tensor("L0A")   # L0A
    # 正在执行MTE2操作， MTE1操作需要等待MTE2完成才能执行。
    l1_weight.set_valid()  # 手动使能L1
    wait_flag("PIPE-MTE2", "PIPE-MTE1", 1)
    x.load(l1_weight)
```

**返回值说明**

无

### wait_flag

**功能说明**

用于确保核内各PIPE间不同指令的同步，pipe_dst等待pipe_src完成调度之后解除阻塞状态。

**接口原型**

```python
wait_flag(pipe_src, pipe_dst, event_id)
```

**参数说明**

|参数名|输入/输出|说明|
|--|--|--|
|pipe_src|输入|源PIPE，在pipe_src调度后设置event_id。<br/>输入格式为aicore_PIPE，例如："aic0_PIPE-MTE1"。其中aicore的取值范围参见基础功能接口Core，PIPE取值范围为"PIPE-MTE1"、"PIPE-MTE2"、 "PIPE-MTE3"、"PIPE-FIX"、"PIPE-M"、"PIPE-V"、 "PIPE-S"。不指定aicore时，可直接输入PIPE取值。<br/>数据类型：string。<br/>必选参数。|
|pipe_dst|输入|目的PIPE，在pipe_src调度之后，pipe_dst将会解除阻塞状态。<br/>输入格式为aicore_PIPE，例如："aic0_PIPE-MTE1"。其中aicore的取值范围参见基础功能接口Core，PIPE取值范围为"PIPE-MTE1"、"PIPE-MTE2"、 "PIPE-MTE3"、"PIPE-FIX"、"PIPE-M"、"PIPE-V"、 "PIPE-S"。不指定aicore时，可直接输入PIPE取值。<br/>数据类型：string。<br/>必选参数。|
|event_id|输入|同步指令之间依赖的唯一值。<br/>取值范围[0, 65535]。<br/>数据类型：int。<br/>必选参数。|

**约束说明**

- 在同一核内set_flag与wait_flag个数需匹配。
- 同核内不应出现重复的set_flag指令。
- 同一核内，当set_flag和wait_flag内的pipe_src和pipe_dst相同时，event_id也应保持唯一。

**使用示例**

```python
from mskpp import Tensor, Chip, set_flag, wait_flag
with Chip("Ascendxxyy") as chip:
    gm_weight = Tensor("GM", "FP16", [128, 256], format="ND")
    l1_weight = Tensor("L1", "FP16", [128, 256], format="ND")
    for conv_idx in range(4):  # L0A数据加载前，GM分批加载到L1上
        gm_weight_part = gm_weight[:, 64]
        l1_weight_part = l1_weight[:, 64]
        l1_weight_part.load(gm_weight_part)
        if conv_idx == 3:
            set_flag("PIPE-MTE2", "PIPE-MTE1", 1)  # 当完成MTE2，才可以执行MTE1
    x = Tensor("L0A")   # L0A
    # 正在执行MTE2操作， MTE1操作需要等待MTE2完成才能执行。
    l1_weight.set_valid()  # 手动使能L1
    wait_flag("PIPE-MTE2", "PIPE-MTE1", 1)
    x.load(l1_weight)
```

**返回值说明**

无

## 指令接口

### mmad

**功能说明**

完成矩阵乘加操作。

**接口原型**

```python
class mmad(x, y, b, is_inited=False)
```

**参数说明**

|参数名|数据类型|说明|
|--|--|--|
|x|Tensor变量|左矩阵，在L0A空间。支持FP16。|
|y|Tensor变量|右矩阵，在L0B空间。支持FP16。|
|b|Tensor变量|偏置项，可以在L0C空间或Bias Table空间。支持FP32。|
|is_inited|bool|当输入是在L0C空间时，需要加is_inited=True，因为不存在通路将数据从GM直接搬运到L0C。|

**约束说明**

偏置项在Bias Table空间时，其Tensor的数据格式需为ND，shape是[n, ]。

**使用示例**

```python
from mskpp import mmad, Tensor
in_x = Tensor("GM", "FP16", [32, 48], format="ND")
in_y = Tensor("GM", "FP16", [48, 16], format="ND")
in_z = Tensor("GM", "FP32", [32, 16], format="NC1HWC0")
out_z = mmad(in_x, in_y, in_z)()
```

**返回值说明**

无

### vadd

**功能说明**

vadd指令抽象。

z = x + y， x、y按元素相加。

**接口原型**

```python
class vadd(x, y, z)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor，支持FP16、FP32、INT16、INT32。|
|y|输入|Tensor变量|输入y向量Tensor，支持FP16、FP32、INT16、INT32。|
|z|输出|Tensor变量|输出向量Tensor。|

**约束说明**

Vector指令所有输入输出数据的Tensor均在“UB“空间中，shape需保持一致。

**使用示例**

```python
from mskpp import vadd, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vadd(ub_x, ub_y, ub_z)()
```

**返回值说明**

无

### vbrcb

**功能说明**

vbrcb指令抽象。

根据指令的stride将Tensor进行扩维，由于目前msKPP工具的指令体系里并没有stride的概念，需要用户填写如何扩维倍数，并保持输入输出Tensor的shape维度一致。

**接口原型**

```python
class vbrcb(x, y, broadcast_num)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor。支持UINT16、UINT32。|
|y|输出|Tensor变量|输出y向量Tensor。支持UINT16、UINT32。|
|broadcast_num|输入|int|指定最后一维扩维到多少倍，实测性能数据不同扩维倍数对性能影响不大，因此直接以常用的扩维16倍数据为准（对应指令的dstBlockStride=1，dstRepeatStride=8）。|

**使用示例**

```python
from mskpp import vbrcb, Tensor
ub_x, ub_y = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
broadcast_num = 16
ub_x.load(gm_x)
out = vbrcb(ub_x, ub_y, broadcast_num)()
```

**返回值说明**

无

### vconv

**功能说明**

vconv指令抽象。

y = vconv(x, dtype)，vconv表示对输入数据进行类型转换的向量计算。

目前支持转换类型包括：BF16->FP32、FP16->FP32、FP16->INT16、FP16->INT32、FP16->INT4、FP16->INT8、FP16->UINT8、FP32->BF16、FP32->FP16、FP32->INT32、FP32->INT64、INT4->FP16、INT64->FP32、INT8->FP16、UINT8->FP16。

**接口原型**

```python
class vconv(x, y, dtype)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor。|
|y|输出|Tensor变量|输出y向量Tensor。|
|dtype|输入|字符串|表示目标Tensor的数据类型。|

**使用示例**

```python
from mskpp import vconv, Tensor
ub_x, ub_y = Tensor("UB", "FP16"), Tensor("UB")
gm_x = Tensor("GM")
ub_x.load(gm_x)
out = vconv(ub_x, ub_y, "FP32")()
```

**返回值说明**

无

### vconv_deq

**功能说明**

vconv_deq指令抽象。

y = vconv_deq(x, dtype)，vconv_deq表示对输入数据进行量化操作的向量计算。

目前支持转换类型包括：FP16->INT8、INT32>FP16。

**接口原型**

```python
class vconv_deq(x, y, dtype)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor。|
|y|输出|Tensor变量|输出y向量Tensor。|
|dtype|输入|字符串|表示目标Tensor的数据类型。|

**使用示例**

```python
from mskpp import vconv_deq, Tensor
ub_x, ub_y = Tensor("UB", "FP16"), Tensor("UB")
gm_x = Tensor("GM")
ub_x.load(gm_x)
out = vconv_deq(ub_x, ub_y, "FP32")()
```

**返回值说明**

无

### vconv_vdeq

**功能说明**

vconv_vdeq指令抽象。

y = vconv_vdeq(x, dtype)，vconv_vdeq表示对输入数据进行量化操作的向量计算。

目前支持转换类型包括：INT16->INT8。

**接口原型**

```python
class vconv_vdeq(x, y, dtype)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor。|
|y|输出|Tensor变量|输出y向量Tensor。|
|dtype|输入|字符串|表示目标Tensor的数据类型。|

**使用示例**

```python
from mskpp import vconv_vdeq, Tensor
ub_x, ub_y = Tensor("UB", "FP16"), Tensor("UB")
gm_x = Tensor("GM")
ub_x.load(gm_x)
out = vconv_vdeq(ub_x, ub_y, "FP32")()
```

**返回值说明**

无

### vector_dup

**功能说明**

vector_dup指令抽象。

y = vector_dup(x)， x、 y按元素进行填充。

**接口原型**

```python
class vector_dup(x, y, fill_shape)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor。支持FP16、FP32、INT16、INT32、UINT16、UINT32。|
|y|输出|Tensor变量|输出y向量Tensor。支持FP16、FP32、INT16、INT32、UINT16、UINT32。|
|fill_shape|输入|list|表示目标Tensor的要被扩充的shape值。|

**约束说明**

由于该指令输入仅一个标量，因此需要创建一个shape为[1]且is_inited=True的Tensor作为模拟标量输入，不增加性能开销。

**使用示例**

```python
from mskpp import vector_dup, Tensor
ub_x = Tensor("UB", "FP16", [1], format="ND", is_inited=True)
ub_y = Tensor("UB")
out = vector_dup(ub_x, ub_y, [8, 2048])()
```

**返回值说明**

无

### vexp

**功能说明**

vexp指令抽象。

y = vexp(x)， x、y按元素取指数。

**接口原型**

```python
class vexp(x, y)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor。支持FP16、FP32。|
|y|输出|Tensor变量|输出y向量Tensor。支持FP16、FP32。|

**使用示例**

```python
from mskpp import vexp, Tensor
ub_x = Tensor("UB")
ub_x.load(gm_x)
ub_y = Tensor("UB")
out = vexp(ub_x, ub_y)()
```

**返回值说明**

无

### vln

**功能说明**

vln指令抽象。

y = vln(x)，x、y按元素取对数。

**接口原型**

```python
class vln(x, y)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor。支持FP16、FP32。|
|y|输出|Tensor变量|输出y向量Tensor。支持FP16、FP32。|

**使用示例**

```python
from mskpp import vln, Tensor
ub_x = Tensor("UB")
gm_x = Tensor("GM")
ub_x.load(gm_x)
ub_y = Tensor("UB")
out = vln(ub_x, ub_y)()
```

**返回值说明**

无

### vmax

**功能说明**

vmax指令抽象。

z = vmax(x, y)，x、y按元素取最大。

**接口原型**

```python
class vmax(x, y, z)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor。支持FP16、FP32、INT16、INT32。|
|y|输入|Tensor变量|输入y向量Tensor。支持FP16、FP32、INT16、INT32。|
|z|输出|Tensor变量|输出向量Tensor。支持FP16、FP32、INT16、INT32。|

**使用示例**

```python
from mskpp import vmax, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vmax(ub_x, ub_y, ub_z)()
```

**返回值说明**

无

### vmul

**功能说明**

vmul指令抽象。

z = x * y，x、y按元素相乘。

**接口原型**

```python
class vmul(x, y, z)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor。支持FP16、FP32、INT16、INT32。|
|y|输入|Tensor变量|输入y向量Tensor。支持FP16、FP32、INT16、INT32。|
|z|输出|Tensor变量|输出向量Tensor。支持FP16、FP32、INT16、INT32。|

**使用示例**

```python
from mskpp import vmul, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vmul(ub_x, ub_y, ub_z)()
```

**返回值说明**

无

### vmuls

**功能说明**

vmuls指令抽象。

z = vmuls(x, y)，vmuls求值向量x与标量y的乘积。

**接口原型**

```python
class vmuls(x, y, z)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入向量Tensor。支持FP16、FP32、INT16、INT32。|
|y|输入|Python标量|输入标量，程序不对该参数做任何处理。|
|z|输出|Tensor变量|输出向量Tensor。支持FP16、FP32、INT16、INT32。|

**使用示例**

```python
from mskpp import vmuls, Tensor
ub_x, ub_z = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
ub_x.load(gm_x)
out = vmuls(ub_x, 5, ub_z)()  //5为y标量的值
```

**返回值说明**

无

### vsub

**功能说明**

vsub指令抽象。

z = x - y，x、y按元素相减。

**接口原型**

```python
class vsub(x, y, z)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor。支持FP16、FP32、INT16、INT32。|
|y|输入|Tensor变量|输入y向量Tensor。支持FP16、FP32、INT16、INT32。|
|z|输出|Tensor变量|输出向量Tensor。支持FP16、FP32、INT16、INT32。|

**使用示例**

```python
from mskpp import vsub, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vsub(ub_x, ub_y, ub_z)()
```

**返回值说明**

无

### vdiv

**功能说明**

vdiv指令抽象。

z = x / y，x、y按元素相除。

**接口原型**

```python
class vdiv(x, y, z)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor。支持FP16、FP32。|
|y|输入|Tensor变量|输入y向量Tensor。支持FP16、FP32。|
|z|输出|Tensor变量|输出向量Tensor。支持FP16、FP32。|

**使用示例**

```python
from mskpp import vdiv, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vdiv(ub_x, ub_y, ub_z)()
```

**返回值说明**

无

### vcadd

**功能说明**

vcadd指令抽象。

根据指令的入参将Tensor进行reduce维度，在msKPP指令体系里由reduce_num控制shape缩减倍数，并保持输入输出Tensor的shape维度一致。当shape最后一维reduce到1，则将该维度消除。需保证shape中最后一维能够被reduce_num整除且不为0。

**接口原型**

```python
class vcadd(x, y, reduce_num)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor。支持FP16、FP32。|
|reduce_num|输入|int|指定最后一维reduce到多少倍，此参数的取值对该指令的性能无影响。|
|y|输出|Tensor变量|输出y向量Tensor。支持FP16、FP32。|

**使用示例**

```python
from mskpp import vcadd, Tensor
ub_x, ub_y = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
reduce_num = 16
ub_x.load(gm_x)
out = vcadd(ub_x, ub_y, reduce_num)()
```

**约束说明**

reduce_num不能为0。

**返回值说明**

无

### vabs

**功能说明**

vabs指令抽象。

y = vabs(x)， x、y按元素取绝对值。

**接口原型**

```python
class vabs(x, y)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor。支持FP16、FP32。|
|y|输出|Tensor变量|输出y向量Tensor。支持FP16、FP32。|

**使用示例**

```python
from mskpp import vabs, Tensor
ub_x, ub_y = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
ub_x.load(gm_x)
out = vabs(ub_x, ub_y)()
```

**返回值说明**

无

### vaddrelu

**功能说明**

vaddrelu指令抽象。

z = vaddrelu(x, y)，x、y按元素相加后再计算relu值。

**接口原型**

```python
class vaddrelu(x, y, z)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor。支持FP16、FP32、INT16。|
|y|输入|Tensor变量|输入y向量Tensor。支持FP16、FP32、INT16。|
|z|输出|Tensor变量|输出向量Tensor。支持FP16、FP32、INT16。|

**使用示例**

```python
from mskpp import vaddrelu, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vaddrelu(ub_x, ub_y, ub_z)()
```

**返回值说明**

无

### vaddreluconv

**功能说明**

vaddreluconv指令抽象。

z = vaddreluconv(x, y)，x、y按元素相加，计算relu值，并对输出做量化操作。

支持的类型转换有FP16->INT8、FP32->FP16、INT16->INT8。

**接口原型**

```python
class vaddreluconv(x, y, z)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor。支持FP16、FP32、INT16。|
|y|输入|Tensor变量|输入y向量Tensor。支持FP16、FP32、INT16。|
|z|输出|Tensor变量|输出向量Tensor。支持FP16、INT8。|

**使用示例**

```python
from mskpp import vaddreluconv, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vaddreluconv(ub_x, ub_y, ub_z)()
```

**返回值说明**

无

### vadds

**功能说明**

vadds指令抽象。

z = vadds(x, y)，vadds求值向量x与标量y的和。

**接口原型**

```python
class vadds(x, y, z)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入向量Tensor。支持FP16、FP32、INT16、INT32。|
|y|输入|Tensor变量|输入标量。程序不对该参数做任何处理。|
|z|输出|Tensor变量|输出向量Tensor。支持FP16、FP32、INT16、INT32。|

**使用示例**

```python
from mskpp import vadds, Tensor
ub_x, ub_z = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
ub_x.load(gm_x)
out = vadds(ub_x, 5, ub_z)() //5为y标量的值
```

**返回值说明**

无

### vand

**功能说明**

vand指令抽象。

vand(x, y, z)，x、y按元素取与，得到z值。

**接口原型**

```python
class vand(x, y, z)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor。支持INT16、UINT16。|
|y|输入|Tensor变量|输入y向量Tensor。支持INT16、UINT16。|
|z|输出|Tensor变量|输出向量Tensor。支持INT16、UINT16。|

**使用示例**

```python
from mskpp import vand, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vand(ub_x, ub_y, ub_z)()
```

**返回值说明**

无

### vaxpy

**功能说明**

vaxpy指令抽象。

z = x * y + z，vaxpy求值向量x与标量y的乘积后加上目标地址z上的和，可以通过if_mix将输出的数据类型格式指定为FP32。

**接口原型**

```python
vaxpy(x, y, z, if_mix=False)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入向量Tensor。支持FP16、FP32、INT16、INT32。|
|y|输入|Tensor变量|输入标量，程序不对该参数做任何处理。|
|z|输出|Tensor变量|输出向量Tensor。支持FP16、FP32、INT16、INT32。|
|if_mix|输入|Tensor变量|默认为False。若设置为True，指定输出数据类型为FP32。|

**使用示例**

```python
from mskpp import vaxpy, Tensor
ub_x, ub_z = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
ub_x.load(gm_x)
out = vaxpy(ub_x, ub_y, ub_z)()
```

**返回值说明**

无

### vbitsort

**功能说明**

vbitsort指令抽象。

根据x输入进行排序，并在排序后给出元素原始的index数据，因此输出向量Tensor的shape会是x数据的两倍。

**接口原型**

```python
class vbitsort(x, y, z)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入向量Tensor。支持FP16、FP32。|
|y|输入|Tensor变量|输入向量Tensor。支持UINT32。|
|z|输出|Tensor变量|输出向量Tensor。支持FP16、FP32。|

**使用示例**

```python
from mskpp import vbitsort, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM") 
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vbitsort(ub_x, ub_y, ub_z)()
```

**返回值说明**

无

### vcgadd

**功能说明**

vcgadd指令抽象

计算每个block元素的和，共计8个block，不支持混合地址。

**接口原型**

```python
class vcgadd(x, y, reduce_num)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor，支持FP16、FP32。|
|y|输出|Tensor变量|输出y向量Tensor，支持FP16、FP32。|
|reduce_num|输入|int|shape指定的缩减倍数。|

**约束说明**

reduce_num不能为0。

**使用示例**

```python
from mskpp import vcgadd, Tensor
ub_x, ub_y = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
reduce_num = 16
ub_x.load(gm_x)
out = vcgadd(ub_x, ub_y, reduce_num)()
```

**返回值说明**

无

### vcgmax

**功能说明**

vcgmax指令抽象

计算每个block的最大元素，共计8个block，不支持混合地址。

**接口原型**

```python
class vcgmax(x, y, reduce_num)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor，支持FP16、FP32。|
|y|输出|Tensor变量|输出y向量Tensor，支持FP16、FP32。|
|reduce_num|输入|int|指定最后一维reduce到多少倍，此参数的取值对该指令的性能无影响。|

**约束说明**

reduce_num不能为0。

**使用示例**

```python
from mskpp import vcgmax, Tensor
ub_x, ub_y = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
reduce_num = 16
ub_x.load(gm_x)
out = vcgmax(ub_x, ub_y, reduce_num)()
```

**返回值说明**

无

### vcgmin

**功能说明**

vcgmin指令抽象

计算每个block的最小元素，共计8个block，不支持混合地址。

**接口原型**

```python
class vcgmin(x, y, reduce_num)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor，支持FP16。|
|y|输出|Tensor变量|输出y向量Tensor，支持FP16。|
|reduce_num|输入|int|指定最后一维reduce到多少倍，实测性能数据reduce对性能无影响。|

**约束说明**

reduce_num不能为0。

**使用示例**

```python
from mskpp import vcgmin, Tensor
ub_x, ub_y = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
reduce_num = 16
ub_x.load(gm_x)
out = vcgmin(ub_x, ub_y, reduce_num)()
```

**返回值说明**

无

### vcmax

**功能说明**

vcmax指令抽象。

计算输入的Vector中的元素最大值。

**接口原型**

```python
class vcmax(x, y, reduce_num)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor，支持FP16、FP32。|
|y|输出|Tensor变量|输出y向量Tensor，支持FP16、FP32。|
|reduce_num|输入|int|指定最后一维reduce到多少倍，实测性能数据reduce对性能无影响。|

**约束说明**

reduce_num不能为0。

**使用示例**

```python
from mskpp import vcmax, Tensor
ub_x, ub_y = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
reduce_num = 16
ub_x.load(gm_x)
out = vcmax(ub_x, ub_y, reduce_num)()
```

**返回值说明**

无

### vcmin

**功能说明**

vcmin指令抽象。

计算输入的Vector中的元素最小值。

**接口原型**

```python
class vcmin(x, y, reduce_num)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor，支持FP16、FP32。|
|y|输出|Tensor变量|输出y向量Tensor，支持FP16、FP32。|
|reduce_num|输入|int|指定最后一维reduce到多少倍，实测性能数据reduce对性能无影响。|

**约束说明**

reduce_num不能为0。

**使用示例**

```python
from mskpp import vcmin, Tensor
ub_x, ub_y = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
reduce_num = 16
ub_x.load(gm_x)
out = vcmin(ub_x, ub_y, reduce_num)()
```

**返回值说明**

无

### vcmp__xxx_

**功能说明**

vcmp_[eq|ge|gt|le|lt|ne]指令抽象，该六条指令性能一致。

vcmp_eq: z = (x == y)， x、y按元素比较相等得到z。

vcmp_ge: z = (x >= y)， x、y按元素比较大于或等于得到z。

vcmp_gt: z = (x > y)， x、y按元素比较大于得到z。

vcmp_le: z = (x <= y)， x、y按元素比较小于或等于得到z。

vcmp_lt: z = (x < y)， x、y按元素比较小于得到z。

vcmp_ne: z = (x != y)， x、y按元素比较不等得到z。

**接口原型**

```python
class vcmp(x, y)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor，支持FP16、FP32。|
|y|输出|Tensor变量|输出y向量Tensor，支持FP16、FP32。|

**约束说明**

Vector指令所有输入输出数据的Tensor均在“UB“空间中，shape需保持一致。

**使用示例**

```python
from mskpp import vcmp, Tensor
ub_x, ub_y = Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vcmp(ub_x, ub_y)()
```

**返回值说明**

无

### vcmpv__xxx_

**功能说明**

vcmpv_[eq|ge|gt|le|lt|ne]指令抽象，该六条指令性能一致。

vcmpv_eq: z = (x == y)， x、y按元素比较相等得到z。

vcmpv_ge: z = (x >= y)， x、y按元素比较大于或等于得到z。

vcmpv_gt: z = (x > y)， x、y按元素比较大于得到z。

vcmpv_le: z = (x <= y)， x、y按元素比较小于或等于得到z。

vcmpv_lt: z = (x < y)， x、y按元素比较小于得到z。

vcmpv_ne: z = (x != y)， x、y按元素比较不等得到z。

**接口原型**

```python
class vcmpv(x, y, z)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor，支持FP16、FP32。|
|y|输入|Tensor变量|输入y向量Tensor，支持FP16、FP32。|
|z|输出|Tensor变量|输出向量Tensor。|

**约束说明**

Vector指令所有输入输出数据的Tensor均在“UB“空间中，shape需保持一致。

**使用示例**

```python
from mskpp import vcmpv, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vcmpv(ub_x, ub_y, ub_z)()
```

**返回值说明**

无

### vcmpvs__xxx_

**功能说明**

vcmpvs_[eq|ge|gt|le|lt|ne]指令抽象，该六条指令性能一致。

vcmpvs_eq: z = (x == y)， x逐元素与y中存储的标量比较相等得到z。

vcmpvs_ge: z = (x >= y)， x逐元素与y中存储的标量比较大于或等于得到z。

vcmpvs_gt: z = (x > y)，x逐元素与y中存储的标量比较大于得到z。

vcmpvs_le: z = (x <= y)， x逐元素与y中存储的标量比较小于或等于得到z。

vcmpvs_lt: z = (x < y)， x逐元素与y中存储的标量比较小于得到z。

vcmpvs_ne: z = (x != y)， x逐元素与y中存储的标量比较不等得到z。

**接口原型**

```python
class vcmpvs(x, y, z)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor，支持FP16、FP32。|
|y|输入|Tensor变量|输入y向量Tensor，支持FP16、FP32。|
|z|输出|Tensor变量|输出向量Tensor。|

**约束说明**

Vector指令所有输入输出数据的Tensor均在“UB“空间中，shape需保持一致。

**使用示例**

```python
from mskpp import vcmpvs, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vcmpvs(ub_x, ub_y, ub_z)()
```

**返回值说明**

无

### vcopy

**功能说明**

vcopy指令抽象

将源地址的Tensor拷贝到目标地址。

**接口原型**

```python
class vcopy(x, y)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入向量Tensor。支持int16、int32、uint16、uint32。|
|y|输出|Tensor变量|输出向量Tensor。支持int16、int32、uint16、uint32。|

**使用示例**

```python
from mskpp import vcopy, Tensor
ub_x, ub_y = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
ub_x.load(gm_x)
out = vcopy(ub_x, ub_y)()
```

**返回值说明**

无

### vcpadd

**功能说明**

vcpadd指令抽象。

计算输入的x向量的n和n+1的和，n为偶数下标，将结果写回y。reduce_num控制了输出的type。

**接口原型**

```python
class vcpadd(x, y, reduce_num)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor。支持fp16、fp32。|
|y|输出|Tensor变量|输出y向量Tensor。支持fp16、fp32。|
|reduce_num|输入|int|shape指定的缩减倍数。|

**使用示例**

```python
from mskpp import vcpadd, Tensor
ub_x, ub_y = Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vcpadd(ub_x, ub_y, reduce_num)()
```

**返回值说明**

无

### vgather

**功能说明**

给定输入的张量和一个地址偏移张量，vgather指令根据偏移地址将输入张量按元素收集到结果张量中。

**接口原型**

```python
class vgather(x, y)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor。支持UINT16、UINT32。|
|y|输出|Tensor变量|输出y向量Tensor。支持UINT16、UINT32。|

**使用示例**

```python
from mskpp import vgather, Tensor
ub_x, ub_y = Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vgather(ub_x, ub_y)()
```

**返回值说明**

无

### vgatherb

**功能说明**

给定一个输入的张量和一个地址偏移张量，vgatherb指令根据偏移地址将输入张量收集到结果张量中。

**接口原型**

```python
class vgatherb(x, y)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor。支持UINT16、UINT32。|
|y|输出|Tensor变量|输出y向量Tensor。支持UINT16、UINT32。|

**使用示例**

```python
from mskpp import vgatherb, Tensor
ub_x, ub_y = Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vgatherb(ub_x, ub_y)()
```

**返回值说明**

无

### vlrelu

**功能说明**

vlrelu指令抽象。

若x大于等于0，则z=x；若x小于0，则z=x*y，x按元素与标量y相乘。

**接口原型**

```python
class vlrelu(x, y, z)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor。支持float16、float32。|
|y|输入|Tensor变量|输入y标量。支持float16、float32。|
|z|输出|Tensor变量|输出向量Tensor。支持float16、float32。|

**使用示例**

```python
from mskpp import vlrelu, Tensor
ub_x, ub_z = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
scalar_y = 5  //5为y标量的值
ub_x.load(gm_x)
out = vlrelu(ub_x, scalar_y, ub_z)()
```

**返回值说明**

无

### vmadd

**功能说明**

vmadd指令抽象。

z = x * z + y。对两个向量中的每个元素执行乘法和加法。

**接口原型**

```python
class vmadd(x, y, z)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor。支持float16、float32。|
|y|输入|Tensor变量|输入y向量Tensor。支持float16、float32。|
|z|输出|Tensor变量|输出向量Tensor。支持float16、float32。|

**使用示例**

```python
from mskpp import vmadd, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vmadd(ub_x, ub_y, ub_z)()
```

**返回值说明**

无

### vmaddrelu

**功能说明**

vmaddrelu指令抽象。

z = RELU(x * z + y)。对两个向量中的每个元素进行乘法和加法，然后对该结果中的每个元素进行MADDRELU操作。

**接口原型**

```python
class vmaddrelu(x, y, z)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor。支持float16、float32。|
|y|输入|Tensor变量|输入y向量Tensor。支持float16、float32。|
|z|输出|Tensor变量|输出向量Tensor。支持float16、float32。|

**使用示例**

```python
from mskpp import vmaddrelu, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vmaddrelu(ub_x, ub_y, ub_z)()
```

**返回值说明**

无

### vmaxs

**功能说明**

vmaxs指令抽象。

对向量中的每个元素和标量进行比较，返回较大者。

**接口原型**

```python
class vmaxs(x, y, z)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor。支持float16、float32、int16、int32。|
|y|输入|Tensor变量|输入标量。程序不对该参数做任何处理。|
|z|输出|Tensor变量|输出向量Tensor。支持float16、float32、int16、int32。|

**使用示例**

```python
from mskpp import vmaxs, Tensor
ub_x, ub_z = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
ub_x.load(gm_x)
out = vmaxs(ub_x, 5, ub_z)()
```

**返回值说明**

无

### vmin

**功能说明**

vmin指令抽象。

对两个向量中的每个元素和标量进行比较，返回较小者。

**接口原型**

```python
class vmin(x, y, z)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor。支持float16、float32、int16、int32。|
|y|输入|Tensor变量|输入y向量Tensor。支持float16、float32、int16、int32。|
|z|输出|Tensor变量|输出向量Tensor。支持float16、float32、int16、int32。|

**使用示例**

```python
from mskpp import vmin, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vmin(ub_x, ub_y, ub_z)()
```

**返回值说明**

无

### vmins

**功能说明**

vmins指令抽象。

对向量中的每个元素和标量进行比较，返回较小者。

**接口原型**

```python
class vmins(x, y, z)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor。支持float16、float32、int16、int32。|
|y|输入|Tensor变量|输入标量。程序不对该参数做任何处理。|
|z|输出|Tensor变量|输出向量Tensor。支持float16、float32、int16、int32。|

**使用示例**

```python
from mskpp import vmins, Tensor
ub_x, ub_z = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
ub_x.load(gm_x)
out = vmins(ub_x, 5, ub_z)()  //5为y的标量值
```

**返回值说明**

无

### vmla

**功能说明**

vmla指令抽象。

z = x * y + z， x、y按元素相乘，相乘的结果与z按元素相加，可以通过if_mix将输出的数据类型格式指定为FP32。

目前支持：

type = f16，f16 = f16 * f16 + f16。

type = f32，f32 = f32 * f32 + f32。

if_mix = True时，f32 = f16 * f16 + f32。其中x、y向量使用64个元素的f16数据用于计算，源向量仅使用低4个block，4个高block被忽略。Xd是64个元素的包含8个block的f32数据，同时作为目标向量和第三个源向量。

**接口原型**

```python
class vmla(x, y, z, if_mix=False)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor，支持FP16、FP32。|
|y|输入|Tensor变量|输入y向量Tensor，支持FP16、FP32。|
|z|输出|Tensor变量|输出向量Tensor，支持FP16、FP32。|
|if_mix|输入|Tensor变量|默认为False。若设置为True，指定输出数据类型为FP32。|

**约束说明**

Vector指令输入输出数据的Tensor均在“UB“空间中。

**使用示例**

```python
from mskpp import vmla, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vmla(ub_x, ub_y, ub_z)()
```

**返回值说明**

无

### vmrgsort

**功能说明**

将已经排好序的最多4条region proposals队列，排列并合并成1条队列，结果按照score域由大到小排序。

**接口原型**

```python
class vmrgsort(x, y, z)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor，支持FP16、FP32。|
|y|输入|Tensor变量|输入y向量Tensor，支持UINT64。|
|z|输出|Tensor变量|输出向量Tensor，支持FP16、FP32。|

**使用示例**

```python
from mskpp import vmrgsort, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vmrgsort(ub_x, ub_y, ub_z)()
```

**返回值说明**

无

### vmulconv

**功能说明**

vmulconv指令抽象。

z = vmulconv(x, y)，x、y按元素相乘，并对输出做量化操作。

**接口原型**

```python
class vmulconv(x, y, z, dtype)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor。支持FP16。|
|y|输入|Tensor变量|输入y向量Tensor。支持FP16。|
|z|输出|Tensor变量|输出向量Tensor。|
|dtype|输入|Tensor变量|指定输入数据类型，包含UINT8、INT8。z的输出数据类型由dtype决定。|

**使用示例**

```python
from mskpp import vmulconv, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vmulconv(ub_x, ub_y, ub_z, 'UINT8')()
```

**返回值说明**

无

### vnot

**功能说明**

vnot指令抽象。

vnot指令对输入向量按位取反，每个向量为8*256bits。

**接口原型**

```python
class vnot(x, y)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor，支持INT16、UINT16。|
|y|输出|Tensor变量|输出y向量Tensor，支持INT16、UINT16。|

**使用示例**

```python
from mskpp import vnot, Tensor
ub_x, ub_y = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
ub_x.load(gm_x)
out = vnot(ub_x, ub_y)()
```

**约束说明**

该指令仅支持普通掩码模式和计数器模式。

**返回值说明**

无

### vor

**功能说明**

vor指令抽象。

vor指令对输入向量按位取或，每个向量为8*256bits。

**接口原型**

```python
class vor(x, y, z)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor，支持INT16、 UINT16。|
|y|输入|Tensor变量|输入y向量Tensor，支持INT16、UINT16。|
|z|输出|Tensor变量|输出z向量Tensor，支持INT16、UINT16。|

**使用示例**

```python
from mskpp import vor, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x,gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vor(ub_x, ub_y, ub_z)()
```

**约束说明**

该指令仅支持普通掩码模式和计数器模式。

**返回值说明**

无

### vrec

**功能说明**

vrec指令抽象。

vrec指令进行浮点倒数估计，找到每个向量的近似倒数估计。

**接口原型**

```python
class vrec(x, y)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor，支持FP16、FP32。|
|y|输出|Tensor变量|输出y向量Tensor，支持FP16、FP32。|

**使用示例**

```python
from mskpp import vrec, Tensor
ub_x, ub_y = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
ub_x.load(gm_x)
out=vrec(ub_x, ub_y)()
```

**返回值说明**

无

### vreduce

**功能说明**

vreduce指令抽象。

vreduce指令根据输入y向量的mask数据，决定取x向量中的某些元素存至z向量，由于msKPP中的Tensor并无实际元素，因此增加了reserve_num的参数，z输出的shape由该参数决定。

**接口原型**

```python
class vreduce(x, y, z, reserve_num)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor。支持UINT16、UINT32。|
|y|输入|Tensor变量|输入y向量Tensor。支持UINT16、UINT32。|
|z|输出|Tensor变量|输出z向量Tensor。支持UINT16、UINT32。|
|reserve_num|输入|int|指定输出元素的个数。|

**使用示例**

```python
from mskpp import vreduce, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y, gm_z = Tensor("GM"), Tensor("GM"), Tensor("GM")
reserve_num = 16
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vreduce(ub_x, ub_y, ub_z, reserve_num)()
gm_z.load(out[0])
```

**返回值说明**

无

### vreducev2

**功能说明**

vreducev2指令抽象。

vreducev2指令根据输入y向量的mask数据，决定取x向量中的某些block级的元素存至z向量，由于msKPP中的Tensor并无相关概念，因此增加了reserve_num的参数，z输出的shape由该参数决定。

**接口原型**

```python
class vreducev2(x, y, z, reserve_num)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor。支持UINT16、UINT32。|
|y|输入|Tensor变量|输入y向量Tensor。支持UINT16、UINT32。|
|z|输出|Tensor变量|输出z向量Tensor。支持UINT16、UINT32。|
|reserve_num|输入|int|指定输出元素的个数。|

**使用示例**

```python
from mskpp import vreducev2, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y, gm_z = Tensor("GM"), Tensor("GM"), Tensor("GM")
reserve_num = 16
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vreducev2(ub_x, ub_y, ub_z, reserve_num)()
gm_z.load(out[0])
```

**返回值说明**

无

### vrelu

**功能说明**

vrelu指令抽象。

每个元素的relu操作，按照元素小于0的取0，大于等于0的取本身。

**接口原型**

```python
class vrelu(x, y)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor。支持float16、float32、int32。|
|y|输出|Tensor变量|输出向量Tensor。支持float16、float32、int32。|

**使用示例**

```python
from mskpp import vrelu, Tensor
ub_x, ub_y = Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vrelu(ub_x, ub_y)()
```

**返回值说明**

无

### vrsqrt

**功能说明**

vrsqrt指令抽象。

浮点数的倒数平方根。

**接口原型**

```python
class vrsqrt(x, y)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor。支持float16、float32。|
|y|输出|Tensor变量|输出向量Tensor。支持float16、float32。|

**使用示例**

```python
from mskpp import vrsqrt, Tensor
ub_x, ub_y = Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vrsqrt(ub_x, ub_y)()
```

**返回值说明**

无

### vsel

**功能说明**

vsel指令抽象。

通常与vcmp合用，根据获得的cmp_mask来选取x，y中对应位置的某个元素。

**接口原型**

```python
class vsel(x, y, z)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor。支持FP16、FP32、INT16、INT32。|
|y|输入|Tensor变量|输入y向量Tensor。支持FP16、FP32、INT16、INT32。|
|z|输出|Tensor变量|输出向量Tensor。支持FP16、FP32、INT16、INT32。|

**使用示例**

```python
from mskpp import vsel, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vsel(ub_x, ub_y, ub_z)()
```

**返回值说明**

无

### vshl

**功能说明**

vshl指令抽象。

根据输入类型进行逻辑左移或算术左移。

**接口原型**

```python
class vshl(x, y)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor。支持UINT16、UINT32、INT16、INT32。|
|y|输出|Tensor变量|输出y向量Tensor。支持UINT16、UINT32、INT16、INT32。|

**使用示例**

```python
from mskpp import vshl, Tensor
ub_x, ub_z = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
ub_x.load(gm_x)
out = vshl(ub_x, ub_z)()
```

**返回值说明**

无

### vshr

**功能说明**

vshr指令抽象。

根据输入类型进行逻辑左移或算术左移。

**接口原型**

```python
class vshr(x, y)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor。支持UINT16、UINT32、INT16、INT32。|
|y|输出|Tensor变量|输出y向量Tensor。支持UINT16、UINT32、INT16、INT32。|

**使用示例**

```python
from mskpp import vshr, Tensor
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vshr(ub_x, ub_y)()
```

**返回值说明**

无

### vsqrt

**功能说明**

vsqrt指令抽象。

y = √x， x按元素开平方根。

**接口原型**

```python
class vsqrt(x, y)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor。支持float16、float32。|
|y|输出|Tensor变量|输出向量Tensor。支持float16、float32。|

**使用示例**

```python
from mskpp import vsqrt, Tensor
ub_x, ub_z = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
ub_x.load(gm_x)
out = vsqrt(ub_x, ub_y)()
```

**约束说明**

输入的值应为正数，否则结果未知并产生异常。

**返回值说明**

无

### vsubrelu

**功能说明**

vsubrelu指令抽象。

z = vsubrelu(x, y)，x、y按元素相减后再计算relu值。

**接口原型**

```python
class vsubrelu (x, y, z)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor。支持float16、float32。|
|y|输入|Tensor变量|输入y向量Tensor。支持float16、float32。|
|z|输出|Tensor变量|输出向量Tensor。支持float16、float32。|

**使用示例**

```python
from mskpp import vsubrelu, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vsubrelu(ub_x, ub_y, ub_z)()
```

**返回值说明**

无

### vsubreluconv

**功能说明**

vsubreluconv指令抽象。

z = vsubreluconv(x, y)，x、y按元素相减，计算relu值，并对输出做量化操作。

支持的类型转换有FP16->INT8、FP32->FP16、INT16->INT8。

**接口原型**

```python
class vsubreluconv(x, y, z)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor。支持FP16、FP32、INT16。|
|y|输入|Tensor变量|输入y向量Tensor。支持FP16、FP32、INT16。|
|z|输出|Tensor变量|输出向量Tensor。支持FP16、INT8。|

**使用示例**

```python
from mskpp import vsubreluconv, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vsubreluconv(ub_x, ub_y, ub_z)()
```

**返回值说明**

无

### vtranspose

**功能说明**

vtranspose指令抽象。

从输入地址x（32字节对齐）开始转置一个16x16矩阵，每个元素为16位，结果输出到y中，输入输出都是连续的512B存储空间。

**接口原型**

```python
class vtranspose (x, y)
```

**参数说明**

|参数名|输入/输出|数据类型|说明|
|--|--|--|--|
|x|输入|Tensor变量|输入x向量Tensor。支持INT16。|
|y|输出|Tensor变量|输出向量Tensor。支持INT16。|

**使用示例**

```python
from mskpp import vtranspose, Tensor
ub_x, ub_y = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
ub_x.load(gm_x)
out = vtranspose(ub_x, ub_y)()
```

**返回值说明**

无
