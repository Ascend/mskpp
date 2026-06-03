# **msKPP API Reference**

## APIs

The msKPP tool provides two types of APIs: basic APIs and instruction APIs. Basic APIs simulate the chip platform and basic data for operator computing. Instruction APIs simulate specific operator instruction operations, including Vector and Cube computing instructions.

**Table 1** msKPP API list

|**API**|Description|
|--|--|
|[Basic APIs](#basic-apis)|-|
|[Chip](#Chip)|Chip platform for performance modeling, which initializes the profile data of the chip.|
|[Core](#Core)|Simulated AI Core inside the chip.|
|[Tensor](#Tensor)|Basic data type for operator execution.|
|[Tensor.load](#Tensor.load)|Data transfer API, which models data transfer between different units.|
|[Synchronization Instruction APIs](#synchronization-instruction-apis)|-|
|[set_flag](#set_flag)|Instruction API for synchronization between pipes in a core, which is used with `wait_flag`.|
|[wait_flag](#wait_flag)|Instruction API for synchronization between pipes in a core, which is used with `set_flag`.|
|[Instruction APIs](#instruction-apis)|-|
|[mmad](#mmad)|API for modeling `mmad` performance of cube instructions.|
|[vadd](#vadd)|API for modeling `vadd` performance of vector instructions.|
|[vbrcb](#vbrcb)|API for modeling `vbrcb` performance of vector instructions.|
|[vconv](#vconv)|API for modeling `vconv` performance of vector instructions.|
|[vconv_deq](#vconv_deq)|API for modeling `vconv_deq` performance of vector instructions.|
|[vconv_vdeq](#vconv_vdeq)|API for modeling `vconv_vdeq` performance of vector instructions.|
|[vector_dup](#vector_dup)|API for modeling `vector_dup` performance of vector instructions.|
|[vexp](#vexp)|API for modeling `vexp` performance of vector instructions.|
|[vln](#vln)|API for modeling `vln` performance of vector instructions.|
|[vmax](#vmax)|API for modeling `vmax` performance of vector instructions.|
|[vmul](#vmul)|API for modeling `vmul` performance of vector instructions.|
|[vmuls](#vmuls)|API for modeling `vmuls` performance of vector instructions.|
|[vsub](#vsub)|API for modeling `vsub` performance of vector instructions.|
|[vdiv](#vdiv)|API for modeling `vdiv` performance of vector instructions.|
|[vcadd](#vcadd)|API for modeling `vcadd` performance of vector instructions.|
|[vabs](#vabs)|API for modeling `vabs` performance of vector instructions.|
|[vaddrelu](#vaddrelu)|API for modeling `vaddrelu` performance of vector instructions.|
|[vaddreluconv](#vaddreluconv)|API for modeling `vaddreluconv` performance of vector instructions.|
|[vadds](#vadds)|API for modeling `vadds` performance of vector instructions.|
|[vand](#vand)|API for modeling `vand` performance of vector instructions.|
|[vaxpy](#vaxpy)|API for modeling `vaxpy` performance of vector instructions.|
|[vbitsort](#vbitsort)|API for modeling `vbitsort` performance of vector instructions.|
|[vcgadd](#vcgadd)|API for modeling `vcgadd` performance of vector instructions.|
|[vcgmax](#vcgmax)|API for modeling `vcgmax` performance of vector instructions.|
|[vcgmin](#vcgmin)|API for modeling `vcgmin` performance of vector instructions.|
|[vcmax](#vcmax)|API for modeling `vcmax` performance of vector instructions.|
|[vcmin](#vcmin)|API for modeling `vcmin` performance of vector instructions.|
|[vcmp__xxx_](#vcmp_xxx)|API for modeling `vcmp_xxx` performance of vector instructions.|
|[vcmpv__xxx_](#vcmpv_xxx)|API for modeling `vcmpv_xxx` performance of vector instructions.|
|[vcmpvs__xxx_](#vcmpvs_xxx)|API for modeling `vcmpvs_xxx` performance of vector instructions.|
|[vcopy](#vcopy)|API for modeling `vcopy` performance of vector instructions.|
|[vcpadd](#vcpadd)|API for modeling `vcpadd` performance of vector instructions.|
|[vgather](#vgather)|API for modeling `vgather` performance of vector instructions.|
|[vgatherb](#vgatherb)|API for modeling `vgatherb` performance of vector instructions.|
|[vlrelu](#vlrelu)|API for modeling `vlrelu` performance of vector instructions.|
|[vmadd](#vmadd)|API for modeling `vmadd` performance of vector instructions.|
|[vmaddrelu](#vmaddrelu)|API for modeling `vmaddrelu` performance of vector instructions.|
|[vmaxs](#vmaxs)|API for modeling `vmaxs` performance of vector instructions.|
|[vmin](#vmin)|API for modeling `vmin` performance of vector instructions.|
|[vmins](#vmins)|API for modeling `vmins` performance of vector instructions.|
|[vmla](#vmla)|API for modeling `vmla` performance of vector instructions.|
|[vmrgsort](#vmrgsort)|API for modeling `vmrgsort` performance of vector instructions.|
|[vmulconv](#vmulconv)|API for modeling `vmulconv` performance of vector instructions.|
|[vnot](#vnot)|API for modeling `vnot` performance of vector instructions.|
|[vor](#vor)|API for modeling `vor` performance of vector instructions.|
|[vrec](#vrec)|API for modeling `vrec` performance of vector instructions.|
|[vreduce](#vreduce)|API for modeling `vreduce` performance of vector instructions.|
|[vreducev2](#vreducev2)|API for modeling `vreducev2` performance of vector instructions.|
|[vrelu](#vrelu)|API for modeling `vrelu` performance of vector instructions.|
|[vrsqrt](#vrsqrt)|API for modeling `vrsqrt` performance of vector instructions.|
|[vsel](#vsel)|API for modeling `vsel` performance of vector instructions.|
|[vshl](#vshl)|API for modeling `vshl` performance of vector instructions.|
|[vshr](#vshr)|API for modeling `vshr` performance of vector instructions.|
|[vsqrt](#vsqrt)|API for modeling `vsqrt` performance of vector instructions.|
|[vsubrelu](#vsubrelu)|API for modeling `vsubrelu` performance of vector instructions.|
|[vsubreluconv](#vsubreluconv)|API for modeling `vsubreluconv` performance of vector instructions.|
|[vtranspose](#vtranspose)|API for modeling `vtranspose` performance of vector instructions.|

## Basic APIs

### <h3 id="Chip">`Chip`</h3>

**Function**

Processor abstraction, which is instantiated and used in the `with` statement to explicitly model a type of the Ascend AI Processor.

**Prototype**

```python
class Chip(name, debug_mode=False)
```

**Parameter Description**

|Parameter|Input Type|Description|
|--|--|--|
|name|String|Processor name. Currently, most data is collected from the Atlas A2 training products/Atlas A2 inference products. You can use `npu-smi info` to view the Ascend AI Processor type of a device.|
|debug_mode|Bool|Whether to enable the debug mode. The default value is `False`. After the debug mode is enabled, you can view the instructions that are not properly executed, but no output is generated.<br>`True`: enabled<br>`False`: disabled|

**Member Description**

|Member|Description|
|--|--|
|chip.enable_trace()|Enables the operator simulation pipeline function to generate the pipeline chart file `trace.json`.|
|chip.enable_metrics()|Enables single instruction and pipeline information, and generates instruction statistics (`Instruction_statistic.csv`), transfer pipeline statistics (`Pipe_statistic.csv`), and instruction proportion pie chart (`instruction_cycle_consumption.html`).|
|chip.set_cache_hit_ratio(config)|Enables manual adjustment of the L2 cache hit ratio. The value of `config` is `{"cache_hit_ratio": 0.6`}. For details, see the cache hit ratio modeling setion.|
|chip.set_prof_summary_path("xxx/PipeUtilization.csv")|`PipeUtilization.csv` is an example of the msProf result, which is used to compare the theoretical values of the pipeline information with values measured by msProf. For details, see "comparison between theoretical values of pipeline information and values measured by msProf".|
|chip.disable_instr_log()|After this function is enabled, the log printing is suppressed after the instruction task is added and scheduled.|

**Constraints**

This class needs to be initialized under the `with` statement.

**Example**

```python
from mskpp import Chip
# For details about how to view the Ascend AI Processor type of the current device, see the following description.
with Chip("Ascendxxxyy") as chip:    # Ascendxxxyy needs to be replaced with the actual processor type.
    chip.enable_trace()   # Call this function to enable the operator simulation pipeline function and generate a pipeline chart file.
    chip.enable_metrics()  # Call this function to enable the single instruction and pipeline information, and generate the transfer pipeline statistics, instruction information statistics, and instruction proportion pie chart.
```

> [!NOTE]NOTE  
> For servers other than the Atlas A3 training products/Atlas A3 inference products: Run the `npu-smi info` command on the server where the Ascend AI Processor is installed to obtain the chip name. Note that the actual value is represented by `AscendChip name`. For example, if the chip name is `xxxyy`, the actual value is `Ascendxxxyy`. If `Ascendxxxyy` is the path of the code sample, set this parameter to `ascendxxxyy`.

**Returns**

None

### <h3 id="Core">`Core`</h3>

**Function**

AI Core abstraction, which is instantiated and used in the `with` statement to model an AI Core type.

**Prototype**

```python
class Core(core_type_name)
```

**Parameter Description**

|Parameter|Input Type|Description|
|--|--|--|
|core_type_name|String|Character string of the Ascend compute unit type, which can be expressed as `AICx` or `AIVx`, where `x` is a number that corresponds to the sequence number of the used AI Cube Core/AI Vector Core. Only one or more characters from [A-Za-z0-9] are supported.|

**Constraints**

This class needs to be initialized under the `with` statement.

**Example**

```python
from mskpp import Core
with Core("AIC0") as aic:
    # Code related to the operator compute logic on AI Cube Core 0.
    ...
```

**Returns**

None

### <h3 id="Tensor">`Tensor`</h3>

**Function**

Onboard tensor abstraction, in which the memory location, data type, size, and format of tensors can be specified as the data dependency identifiers of instructions.

**Prototype**

```python
class Tensor(mem_type, dtype=None, size=None, format=None, is_inited=False)
```

**Parameter Description**

|Parameter|Input Type|Description|
|--|--|--|
|mem_type|String|Location of the memory space where the abstracted tensor is located, such as GM, UB, L1, L0A, L0B, L0C, FB, and BT.|
|dtype|String|Data type, such as BOOL, UINT1, UINT2, UINT8, UINT16, UINT32, BF16, UINT64, INT4, INT8, INT16, INT32, INT64, FP16, and FP32.|
|size|List|Shape of a tensor.|
|format|String|Data layout format. For details, see "Programming Guide" > "Concepts and Terms" > "Neural Networks and Operators" > "Data Layout Format" in Ascend C Operator Development Guide.|
|is_inited|Bool|Switch that indicates whether the tensor class is ready. Once enabled, instructions that utilize the tensors as the input can be initiated.|

**Member Description**

|Member|Description|
|--|--|
|tensor.set_valid()|Enables the current tensor to be ready. Once enabled, instructions that utilize the tensor as the input can be initiated immediately.|
|tensor.set_invalid()|Disables the current tensor to be ready. Once disabled, instructions that utilize the tensor as the input cannot be initiated immediately.|
|tensor.is_valid()|Obtains the current tensor ready status.|

**Constraints**

You need to create a tensor whose shape is `[1]` and `is_inited=True` for scalar creation.

**Example**

```python
from mskpp import Tensor, Core
gm_tmp= Tensor("GM", "FP16", [48, 16], format="ND")
with Core("AIV0") as aiv:  # Computing logic on AIV0.
    ...
    gm_tmp.load(result, set_value=0)
with Core("AIC0") as aic:
    in_x = Tensor("GM", "FP16", [48, 16], format="ND")
    in_x.load(gm_tmp, expect_value=0) # Computing logic on AIC0.
    ...
```

**Returns**

None

### <h3 id="Tensor.load">`Tensor.load`</h3>

**Function**

All data transfer instructions in the msKPP tool are abstracted as the load method, and users only need to focus on the reasonable transfer channels in Ascend AI Processors, without considering the complex stride concept in the transfer instructions.

**Prototype**

```python
Tensor.load(tensor, repeat=1, set_value=-1, expect_value=-1)
```

**Parameter Description**

|Parameter|Input Type|Description|
|--|--|--|
|tensor|Variable|Another input tensor, whose function is the same as that defined in the API.|
|repeat|int|This parameter simulates the transfer instruction `repeat`. You can input this parameter to obtain the bandwidth of each transfer channel with varying `repeat` values. The bandwidth is used to calculate the time consumed by the transfer instruction. This parameter is optional. The default value is `1`. You are advised to set it to an integer within the range of [1, 255]. If the input value of `repeat` does not meet the requirement, the system throws exception "input repeat = *xx* invalid." where *xx* is the input abnormal value of `repeat`.|
|set_value|int|Identifier indicating that the tensor data is dependent by others. This parameter can be customized and must be used in conjunction with `expect_value`. This parameter is optional. If it is not specified, the dependency relationship is not enabled.|
|expect_value|int|Identifier indicating that loading of the tensor data depends on other data. This parameter can be customized and must be used in conjunction with `set_value`. This parameter is optional. If it is not specified, the dependency relationship is not enabled.|

**Constraints**

`set_value` and `expect_value` must be used in pairs. Otherwise, pipeline blocking may occur.

The `repeat` parameter supports only the following four transfer channels: L1_TO_L0A, L1_TO_L0B, GM_TO_L0A, and GM_TO_L0B.

**Returns**

None

## Synchronization Instruction APIs

### `set_flag`

**Function**

Ensures the synchronization of different instructions between pipelines in a core. After `pipe_src` is scheduled, `pipe_dst` is unblocked. After `set_flag` and `wait_flag` are set, the [Instruction Pipeline Chart (Using MindStudio Insight as an Example)](https://www.hiascend.com/document/detail/zh/mindstudio/82RC1/ODtools/Operatordevelopmenttools/atlasopdev_16_0087.html) will better meet the user's expectations.

**Prototype**

```python
set_flag(pipe_src, pipe_dst, event_id)
```

**Parameter Description**

|Parameter|Input/Output|Description|
|--|--|--|
|pipe_src|Input|Source pipeline. After `pipe_src` is scheduled, set `event_id`.<br>The input format is `aicore_PIPE`, for example, `aic0_PIPE-MTE1`. For details about the value range of `aicore`, see the basic function API `Core`. The value range of `PIPE` is `PIPE-MTE1`, `PIPE-MTE2`, `PIPE-MTE3`, `PIPE-FIX`, `PIPE-M`, `PIPE-V`, and `PIPE-S`. If `aicore` is not specified, you can directly enter the value of `PIPE`.<br>Data type: string.<br>This parameter is required.|
|pipe_dst|Input|Destination pipeline. After `pipe_src` is scheduled, `pipe_dst` is unblocked.<br>The input format is `aicore_PIPE`, for example, `aic0_PIPE-MTE1`. For details about the value range of `aicore`, see the basic function API `Core`. The value range of `PIPE` is `PIPE-MTE1`, `PIPE-MTE2`, `PIPE-MTE3`, `PIPE-FIX`, `PIPE-M`, `PIPE-V`, and `PIPE-S`. If `aicore` is not specified, you can directly enter the value of `PIPE`.<br>Data type: string.<br>This parameter is required.|
|event_id|Input|Unique value of the dependency across synchronization instructions.<br>Value range: [0, 65535]<br>Data type: int.<br>This parameter is required.|

**Constraints**

- The number of `set_flag` instructions must match the number of `wait_flag` instructions in the same core.
- Duplicate `set_flag` instructions should not exist in the same core.
- In the same core, if the values of `pipe_src` and `pipe_dst` in `set_flag` and `wait_flag` are the same, `event_id` must be unique.

**Example**

```python
from mskpp import Tensor, Chip, set_flag, wait_flag
with Chip("Ascendxxyy") as chip:
    gm_weight = Tensor("GM", "FP16", [128, 256], format="ND")
    l1_weight = Tensor("L1", "FP16", [128, 256], format="ND")
    for conv_idx in range(4):  # Before data is loaded to L0A, the GM is loaded to L1 in batches.
        gm_weight_part = gm_weight[:, 64]
        l1_weight_part = l1_weight[:, 64]
        l1_weight_part.load(gm_weight_part)
        if conv_idx == 3:
            set_flag("PIPE-MTE2", "PIPE-MTE1", 1)  # MTE1 can be executed only after MTE2 execution is complete.
    x = Tensor("L0A")   # L0A
    # MTE2 is being executed. MTE1 can be executed only after MTE2 execution is complete.
    l1_weight.set_valid()  # Manually enable L1.
    wait_flag("PIPE-MTE2", "PIPE-MTE1", 1)
    x.load(l1_weight)
```

**Returns**

None

### `wait_flag`

**Function**

Ensures the synchronization of different instructions across pipelines in a core. `pipe_dst` is unblocked after `pipe_src` is scheduled.

**Prototype**

```python
wait_flag(pipe_src, pipe_dst, event_id)
```

**Parameter Description**

|Parameter|Input/Output|Description|
|--|--|--|
|pipe_src|Input|Source pipeline. After `pipe_src` is scheduled, set `event_id`.<br>The input format is `aicore_PIPE`, for example, `aic0_PIPE-MTE1`. For details about the value range of `aicore`, see the basic function API `Core`. The value range of `PIPE` is `PIPE-MTE1`, `PIPE-MTE2`, `PIPE-MTE3`, `PIPE-FIX`, `PIPE-M`, `PIPE-V`, and `PIPE-S`. If `aicore` is not specified, you can directly enter the value of `PIPE`.<br>Data type: string.<br>This parameter is required.|
|pipe_dst|Input|Destination pipeline. After `pipe_src` is scheduled, `pipe_dst` is unblocked.<br>The input format is `aicore_PIPE`, for example, `aic0_PIPE-MTE1`. For details about the value range of `aicore`, see the basic function API `Core`. The value range of `PIPE` is `PIPE-MTE1`, `PIPE-MTE2`, `PIPE-MTE3`, `PIPE-FIX`, `PIPE-M`, `PIPE-V`, and `PIPE-S`. If `aicore` is not specified, you can directly enter the value of `PIPE`.<br>Data type: string.<br>This parameter is required.|
|event_id|Input|Unique value of the dependency across synchronization instructions.<br>Value range: [0, 65535]<br>Data type: int.<br>This parameter is required.|

**Constraints**

- The number of `set_flag` instructions must match the number of `wait_flag` instructions in the same core.
- Duplicate `set_flag` instructions should not exist in the same core.
- In the same core, if the values of `pipe_src` and `pipe_dst` in `set_flag` and `wait_flag` are the same, `event_id` must be unique.

**Example**

```python
from mskpp import Tensor, Chip, set_flag, wait_flag
with Chip("Ascendxxyy") as chip:
    gm_weight = Tensor("GM", "FP16", [128, 256], format="ND")
    l1_weight = Tensor("L1", "FP16", [128, 256], format="ND")
    for conv_idx in range(4):  # Before data is loaded to L0A, the GM is loaded to L1 in batches.
        gm_weight_part = gm_weight[:, 64]
        l1_weight_part = l1_weight[:, 64]
        l1_weight_part.load(gm_weight_part)
        if conv_idx == 3:
            set_flag("PIPE-MTE2", "PIPE-MTE1", 1)  # MTE1 can be executed only after MTE2 is executed.
    x = Tensor("L0A")   # L0A
    # MTE2 is being executed. MTE1 can be executed only after MTE2 execution is complete.
    l1_weight.set_valid()  # Manually enable L1.
    wait_flag("PIPE-MTE2", "PIPE-MTE1", 1)
    x.load(l1_weight)
```

**Returns**

None

## Instruction APIs

### `mmad`

**Function**

Performs matrix multiplication and addition.

**Prototype**

```python
class mmad(x, y, b, is_inited=False)
```

**Parameter Description**

|Parameter|Data Type|Description|
|--|--|--|
|x|Tensor variable|Left matrix in the L0A space. FP16 is supported.|
|y|Tensor variable|Right matrix in the L0B space. FP16 is supported.|
|b|Tensor variable|Bias, which can be in the L0C space or bias table space. FP32 is supported|
|is_inited|Bool|When the input is in the L0C space, `is_inited=True` needs to be added because there is no direct channel to transfer data from the GM to the L0C.|

**Constraints**

When the bias term is in the bias table space, the tensor data format must be ND and shape must be `[n, ]`.

**Example**

```python
from mskpp import mmad, Tensor
in_x = Tensor("GM", "FP16", [32, 48], format="ND")
in_y = Tensor("GM", "FP16", [48, 16], format="ND")
in_z = Tensor("GM", "FP32", [32, 16], format="NC1HWC0")
out_z = mmad(in_x, in_y, in_z)()
```

**Returns**

None

### `vadd`

**Function**

`vadd` instruction abstraction.

`z = x + y`, where `x` and `y` are added by element.

**Prototype**

```python
class vadd(x, y, z)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. FP16, FP32, INT16, and INT32 are supported.|
|y|Input|Tensor variable|Input `y` vector tensor. FP16, FP32, INT16, and INT32 are supported.|
|z|Output|Tensor variable|Output vector tensor.|

**Constraints**

The tensors of all input and output data of vector instructions are in the UB space, and their shapes must be the same.

**Example**

```python
from mskpp import vadd, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vadd(ub_x, ub_y, ub_z)()
```

**Returns**

None

### `vbrcb`

**Function**

`vbrcb` instruction abstraction.

Expands the dimensions of the tensors based on the instruction stride. However, the msKPP instruction system does not support stride. Therefore, you need to specify the dimension expansion factor and ensure that the shapes of the input and output tensors are the same.

**Prototype**

```python
class vbrcb(x, y, broadcast_num)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. UINT16 and UINT32 are supported.|
|y|Output|Tensor variable|Output `y` vector tensor. UINT16 and UINT32 are supported.|
|broadcast_num|Input|Int|Number of times that the last dimension is expanded. Empirical profile data shows that different expansion factors have little impact on performance. Therefore, the standard expansion factor of 16, denoted as `dstBlockStride=1` and `dstRepeatStride=8` in the instruction, is commonly employed.|

**Example**

```python
from mskpp import vbrcb, Tensor
ub_x, ub_y = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
broadcast_num = 16
ub_x.load(gm_x)
out = vbrcb(ub_x, ub_y, broadcast_num)()
```

**Returns**

None

### `vconv`

**Function**

`vconv` instruction abstraction.

`y = vconv(x, dtype)`, where `vconv` indicates the vector calculation for type conversion of input data.

Currently, the following type conversion is supported: BF16->FP32, FP16->FP32, FP16->INT16, FP16->INT32, FP16->INT4, FP16->INT8, FP16->UINT8, FP32->BF16, FP32->FP16, FP32->INT32, FP32->INT64, INT4->FP16, INT64->FP32, INT8->FP16, and UINT8->FP16.

**Prototype**

```python
class vconv(x, y, dtype)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor.|
|y|Output|Tensor variable|Output `y` vector tensor.|
|dtype|Input|String|Data type of the target tensor.|

**Example**

```python
from mskpp import vconv, Tensor
ub_x, ub_y = Tensor("UB", "FP16"), Tensor("UB")
gm_x = Tensor("GM")
ub_x.load(gm_x)
out = vconv(ub_x, ub_y, "FP32")()
```

**Returns**

None

### `vconv_deq`

**Function**

`vconv_deq` instruction abstraction.

`y = vconv_deq(x, dtype)`, where `vconv_deq` indicates vector calculation for quantization on input data.

Currently, conversions from FP16 to INT8 and from INT32 to FP16 are supported.

**Prototype**

```python
class vconv_deq(x, y, dtype)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor.|
|y|Output|Tensor variable|Output `y` vector tensor.|
|dtype|Input|String|Data type of the target tensor.|

**Example**

```python
from mskpp import vconv_deq, Tensor
ub_x, ub_y = Tensor("UB", "FP16"), Tensor("UB")
gm_x = Tensor("GM")
ub_x.load(gm_x)
out = vconv_deq(ub_x, ub_y, "FP32")()
```

**Returns**

None

### `vconv_vdeq`

**Function**

`vconv_vdeq` instruction abstraction.

`y = vconv_vdeq(x, dtype)`, where `vconv_vdeq` indicates vector calculation for quantization on input data.

Currently, the conversion from INT16 to INT8 is supported.

**Prototype**

```python
class vconv_vdeq(x, y, dtype)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor.|
|y|Output|Tensor variable|Output `y` vector tensor.|
|dtype|Input|String|Data type of the target tensor.|

**Example**

```python
from mskpp import vconv_vdeq, Tensor
ub_x, ub_y = Tensor("UB", "FP16"), Tensor("UB")
gm_x = Tensor("GM")
ub_x.load(gm_x)
out = vconv_vdeq(ub_x, ub_y, "FP32")()
```

**Returns**

None

### `vector_dup`

**Function**

`vector_dup` instruction abstraction.

`y = vector_dup(x)`, where `x` and `y` are filled in by element.

**Prototype**

```python
class vector_dup(x, y, fill_shape)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. FP16, FP32, INT16, INT32, UINT16, and UINT32 are supported.|
|y|Output|Tensor variable|Output `y` vector tensor. FP16, FP32, INT16, INT32, UINT16, and UINT32 are supported.|
|fill_shape|Input|List|Shape value to be expanded of the target tensor.|

**Constraints**

Since the input to this instruction is only a scalar, you need to create a tensor whose shape is `[1]` and `is_inited=True` as the simulated scalar input, without increasing performance overhead.

**Example**

```python
from mskpp import vector_dup, Tensor
ub_x = Tensor("UB", "FP16", [1], format="ND", is_inited=True)
ub_y = Tensor("UB")
out = vector_dup(ub_x, ub_y, [8, 2048])()
```

**Returns**

None

### `vexp`

**Function**

`vexp` instruction abstraction.

`y = vexp(x)`, where `x` and `y` take exponents by element.

**Prototype**

```python
class vexp(x, y)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. FP16 and FP32 are supported.|
|y|Output|Tensor variable|Output `y` vector tensor. FP16 and FP32 are supported.|

**Example**

```python
from mskpp import vexp, Tensor
ub_x = Tensor("UB")
ub_x.load(gm_x)
ub_y = Tensor("UB")
out = vexp(ub_x, ub_y)()
```

**Returns**

None

### `vln`

**Function**

`vln` instruction abstraction.

`y = vln(x)`, where `x` and `y` take logarithms by element.

**Prototype**

```python
class vln(x, y)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. FP16 and FP32 are supported.|
|y|Output|Tensor variable|Output `y` vector tensor. FP16 and FP32 are supported.|

**Example**

```python
from mskpp import vln, Tensor
ub_x = Tensor("UB")
gm_x = Tensor("GM")
ub_x.load(gm_x)
ub_y = Tensor("UB")
out = vln(ub_x, ub_y)()
```

**Returns**

None

### `vmax`

**Function**

`vmax` instruction abstraction.

`z = vmax(x, y)`, where `x` and `y` take the maximum value by element.

**Prototype**

```python
class vmax(x, y, z)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. FP16, FP32, INT16, and INT32 are supported.|
|y|Input|Tensor variable|Input `y` vector tensor. FP16, FP32, INT16, and INT32 are supported.|
|z|Output|Tensor variable|Output vector tensor. FP16, FP32, INT16, and INT32 are supported.|

**Example**

```python
from mskpp import vmax, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vmax(ub_x, ub_y, ub_z)()
```

**Returns**

None

### `vmul`

**Function**

`vmul` instruction abstraction.

`z = x * y`, where `x` and `y` are multiplied by element.

**Prototype**

```python
class vmul(x, y, z)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. FP16, FP32, INT16, and INT32 are supported.|
|y|Input|Tensor variable|Input `y` vector tensor. FP16, FP32, INT16, and INT32 are supported.|
|z|Output|Tensor variable|Output vector tensor. FP16, FP32, INT16, and INT32 are supported.|

**Example**

```python
from mskpp import vmul, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vmul(ub_x, ub_y, ub_z)()
```

**Returns**

None

### `vmuls`

**Function**

`vmuls` instruction abstraction.

`z = vmuls(x, y)`, where `vmuls` evaluates the product of vector `x` and scalar `y`.

**Prototype**

```python
class vmuls(x, y, z)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input vector tensor. FP16, FP32, INT16, and INT32 are supported.|
|y|Input|Python scalar|Input scalar. The program does not process this parameter.|
|z|Output|Tensor variable|Output vector tensor. FP16, FP32, INT16, and INT32 are supported.|

**Example**

```python
from mskpp import vmuls, Tensor
ub_x, ub_z = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
ub_x.load(gm_x)
out = vmuls(ub_x, 5, ub_z)()  // 5 is the value of scalar y.
```

**Returns**

None

### `vsub`

**Function**

`vsub` instruction abstraction.

`z = x - y`, where `x` is subtracted by `y` by element.

**Prototype**

```python
class vsub(x, y, z)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. FP16, FP32, INT16, and INT32 are supported.|
|y|Input|Tensor variable|Input `y` vector tensor. FP16, FP32, INT16, and INT32 are supported.|
|z|Output|Tensor variable|Output vector tensor. FP16, FP32, INT16, and INT32 are supported.|

**Example**

```python
from mskpp import vsub, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vsub(ub_x, ub_y, ub_z)()
```

**Returns**

None

### `vdiv`

**Function**

`vdiv` instruction abstraction.

`z = x/y`, where `x` is divided by `y` by element.

**Prototype**

```python
class vdiv(x, y, z)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. FP16 and FP32 are supported.|
|y|Input|Tensor variable|Input `y` vector tensor. FP16 and FP32 are supported.|
|z|Output|Tensor variable|Output vector tensor. FP16 and FP32 are supported.|

**Example**

```python
from mskpp import vdiv, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vdiv(ub_x, ub_y, ub_z)()
```

**Returns**

None

### `vcadd`

**Function**

`vcadd` instruction abstraction.

Reduces the tensor dimensions based on the input parameters of the instruction. In the msKPP instruction system, `reduce_num` controls the shape reduction multiple and ensures that the shapes of the input and output tensors are the same. When the last dimension of the shape is reduced to `1`, the dimension is eliminated. Ensure that the last dimension of the shape can be exactly divided by `reduce_num` and is not `0`.

**Prototype**

```python
class vcadd(x, y, reduce_num)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. FP16 and FP32 are supported.|
|reduce_num|Input|Int|Number of times that the last dimension is reduced. The value of this parameter does not affect the instruction performance.|
|y|Output|Tensor variable|Output `y` vector tensor. FP16 and FP32 are supported.|

**Example**

```python
from mskpp import vcadd, Tensor
ub_x, ub_y = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
reduce_num = 16
ub_x.load(gm_x)
out = vcadd(ub_x, ub_y, reduce_num)()
```

**Constraints**

The value of `reduce_num` cannot be `0`.

**Returns**

None

### `vabs`

**Function**

`vabs` instruction abstraction.

`y = vabs(x)`, where `x` and `y` take the absolute value by element.

**Prototype**

```python
class vabs(x, y)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. FP16 and FP32 are supported.|
|y|Output|Tensor variable|Output `y` vector tensor. FP16 and FP32 are supported.|

**Example**

```python
from mskpp import vabs, Tensor
ub_x, ub_y = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
ub_x.load(gm_x)
out = vabs(ub_x, ub_y)()
```

**Returns**

None

### `vaddrelu`

**Function**

`vaddrelu` instruction abstraction.

`z = vaddrelu(x, y)`, where `x` and `y` are added by element before the relu value is calculated.

**Prototype**

```python
class vaddrelu(x, y, z)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. FP16, FP32, and INT16 are supported.|
|y|Input|Tensor variable|Input `y` vector tensor. FP16, FP32, and INT16 are supported.|
|z|Output|Tensor variable|Output vector tensor. FP16, FP32, and INT16 are supported.|

**Example**

```python
from mskpp import vaddrelu, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vaddrelu(ub_x, ub_y, ub_z)()
```

**Returns**

None

### `vaddreluconv`

**Function**

`vaddreluconv` instruction abstraction.

`z = vaddreluconv(x, y)`, where `x` and `y` are added by element, the relu value is calculated, and the output is quantized.

The following conversion types are supported: FP16->INT8, FP32->FP16, and INT16->INT8.

**Prototype**

```python
class vaddreluconv(x, y, z)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. FP16, FP32, and INT16 are supported.|
|y|Input|Tensor variable|Input `y` vector tensor. FP16, FP32, and INT16 are supported.|
|z|Output|Tensor variable|Output vector tensor. FP16 and INT8 are supported.|

**Example**

```python
from mskpp import vaddreluconv, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vaddreluconv(ub_x, ub_y, ub_z)()
```

**Returns**

None

### `vadds`

**Function**

`vadds` instruction abstraction.

`z = vadds(x, y)`, where `vadds` evaluates the sum of vector `x` and scalar `y`.

**Prototype**

```python
class vadds(x, y, z)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input vector tensor. FP16, FP32, INT16, and INT32 are supported.|
|y|Input|Tensor variable|Input scalar. The program does not process this parameter.|
|z|Output|Tensor variable|Output vector tensor. FP16, FP32, INT16, and INT32 are supported.|

**Example**

```python
from mskpp import vadds, Tensor
ub_x, ub_z = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
ub_x.load(gm_x)
out = vadds(ub_x, 5, ub_z)() // 5 is the value of scalar y.
```

**Returns**

None

### `vand`

**Function**

`vand` instruction abstraction.

`vand(x, y, z)`, where `z` can be obtained when `x` and `y` perform AND operation by element.

**Prototype**

```python
class vand(x, y, z)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. INT16 and UINT16 are supported.|
|y|Input|Tensor variable|Input `y` vector tensor. INT16 and UINT16 are supported.|
|z|Output|Tensor variable|Output vector tensor. INT16 and UINT16 are supported.|

**Example**

```python
from mskpp import vand, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vand(ub_x, ub_y, ub_z)()
```

**Returns**

None

### `vaxpy`

**Function**

`vaxpy` instruction abstraction.

`z = x * y + z`. vaxpy calculates the product of vector `x` and scalar `y`, and adds the target address `z`. The output data type can be specified as FP32 by using `if_mix`.

**Prototype**

```python
vaxpy(x, y, z, if_mix=False)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input vector tensor. FP16, FP32, INT16, and INT32 are supported.|
|y|Input|Tensor variable|Input scalar. The program does not process this parameter.|
|z|Output|Tensor variable|Output vector tensor. FP16, FP32, INT16, and INT32 are supported.|
|if_mix|Input|Tensor variable|The default value is `False`. If this parameter is set to `True`, the output data type is FP32.|

**Example**

```python
from mskpp import vaxpy, Tensor
ub_x, ub_z = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
ub_x.load(gm_x)
out = vaxpy(ub_x, ub_y, ub_z)()
```

**Returns**

None

### `vbitsort`

**Function**

`vbitsort` instruction abstraction.

Sorts data based on the x input and provides the original index data of the elements after sorting. Therefore, the shape of the output vector tensor is twice that of the x data.

**Prototype**

```python
class vbitsort(x, y, z)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input vector tensor. FP16 and FP32 are supported.|
|y|Input|Tensor variable|Input vector tensor. UINT32 is supported.|
|z|Output|Tensor variable|Output vector tensor. FP16 and FP32 are supported.|

**Example**

```python
from mskpp import vbitsort, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM") 
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vbitsort(ub_x, ub_y, ub_z)()
```

**Returns**

None

### `vcgadd`

**Function**

`vcgadd` instruction abstraction.

Calculates the sum of elements in each block. There are eight blocks in total. Mixed addresses are not supported.

**Prototype**

```python
class vcgadd(x, y, reduce_num)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. FP16 and FP32 are supported.|
|y|Output|Tensor variable|Output `y` vector tensor. FP16 and FP32 are supported.|
|reduce_num|Input|Int|Reduction factor for the shape.|

**Constraints**

The value of `reduce_num` cannot be `0`.

**Example**

```python
from mskpp import vcgadd, Tensor
ub_x, ub_y = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
reduce_num = 16
ub_x.load(gm_x)
out = vcgadd(ub_x, ub_y, reduce_num)()
```

**Returns**

None

### `vcgmax`

**Function**

`vcgmax` instruction abstraction.

Calculates the maximum element of each block. There are eight blocks in total. Mixed addresses are not supported.

**Prototype**

```python
class vcgmax(x, y, reduce_num)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. FP16 and FP32 are supported.|
|y|Output|Tensor variable|Output `y` vector tensor. FP16 and FP32 are supported.|
|reduce_num|Input|Int|Number of times that the last dimension is reduced. The value of this parameter does not affect the instruction performance.|

**Constraints**

The value of `reduce_num` cannot be `0`.

**Example**

```python
from mskpp import vcgmax, Tensor
ub_x, ub_y = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
reduce_num = 16
ub_x.load(gm_x)
out = vcgmax(ub_x, ub_y, reduce_num)()
```

**Returns**

None

### `vcgmin`

**Function**

`vcgmin` instruction abstraction.

Calculates the minimum element of each block. There are eight blocks in total. Mixed addresses are not supported.

**Prototype**

```python
class vcgmin(x, y, reduce_num)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. FP16 is supported.|
|y|Output|Tensor variable|Output `y` vector tensor. FP16 is supported.|
|reduce_num|Input|Int|Reduction factor for the last dimension. Empirical profile data shows that the reduction has no impact on performance.|

**Constraints**

The value of `reduce_num` cannot be `0`.

**Example**

```python
from mskpp import vcgmin, Tensor
ub_x, ub_y = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
reduce_num = 16
ub_x.load(gm_x)
out = vcgmin(ub_x, ub_y, reduce_num)()
```

**Returns**

None

### `vcmax`

**Function**

`vcmax` instruction abstraction.

Calculates the maximum element value in the input vector.

**Prototype**

```python
class vcmax(x, y, reduce_num)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. FP16 and FP32 are supported.|
|y|Output|Tensor variable|Output `y` vector tensor. FP16 and FP32 are supported.|
|reduce_num|Input|Int|Reduction factor for the last dimension. Empirical profile data shows that the reduction has no impact on performance.|

**Constraints**

The value of `reduce_num` cannot be `0`.

**Example**

```python
from mskpp import vcmax, Tensor
ub_x, ub_y = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
reduce_num = 16
ub_x.load(gm_x)
out = vcmax(ub_x, ub_y, reduce_num)()
```

**Returns**

None

### `vcmin`

**Function**

`vcmin` instruction abstraction.

Calculates the minimum element value in the input vector.

**Prototype**

```python
class vcmin(x, y, reduce_num)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. FP16 and FP32 are supported.|
|y|Output|Tensor variable|Output `y` vector tensor. FP16 and FP32 are supported.|
|reduce_num|Input|Int|Reduction factor for the last dimension. Empirical profile data shows that the reduction has no impact on performance.|

**Constraints**

The value of `reduce_num` cannot be `0`.

**Example**

```python
from mskpp import vcmin, Tensor
ub_x, ub_y = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
reduce_num = 16
ub_x.load(gm_x)
out = vcmin(ub_x, ub_y, reduce_num)()
```

**Returns**

None

### `vcmp_xxx`

**Function**

`vcmp_[eq|ge|gt|le|lt|ne]` instruction abstraction. The following six instructions have the same performance.

`vcmp_eq: z = (x == y)`, where `z` can be obtained when `x` is equal to `y` by element-wise comparison.

`vcmp_ge: z = (x >= y)`, where `z` can be obtained when `x` is greater than or equal to `y` by element-wise comparison.

`vcmp_gt: z = (x > y)`, where `z` can be obtained when `x` is greater than `y` by element-wise comparison.

`vcmp_le: z = (x <= y)`, where `z` can be obtained when `x` is less than or equal to `y` by element-wise comparison.

`vcmp_lt: z = (x < y)`, where `z` can be obtained when `x` is smaller than `y` by element-wise comparison.

`vcmp_ne: z = (x != y)`, where `z` can be obtained when `x` is not equal to `y` by element-wise comparison.

**Prototype**

```python
class vcmp(x, y)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. FP16 and FP32 are supported.|
|y|Output|Tensor variable|Output `y` vector tensor. FP16 and FP32 are supported.|

**Constraints**

The tensors of all input and output data of vector instructions are in the UB space, and their shapes must be the same.

**Example**

```python
from mskpp import vcmp, Tensor
ub_x, ub_y = Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vcmp(ub_x, ub_y)()
```

**Returns**

None

### `vcmpv_xxx`

**Function**

`vcmpv_[eq|ge|gt|le|lt|ne]` instruction abstraction. The following six instructions have the same performance.

`vcmpv_eq: z = (x == y)`, where `z` can be obtained when `x` is equal to `y` by element-wise comparison.

`vcmpv_ge: z = (x >= y)`, where `z` can be obtained when `x` is greater than or equal to `y` by element-wise comparison.

`vcmpv_gt: z = (x > y)`, where `z` can be obtained when `x` is greater than `y` by element-wise comparison.

`vcmpv_le: z = (x <= y)`, where `z` can be obtained when `x` is less than or equal to `y` by element-wise comparison.

`vcmpv_lt: z = (x < y)`, where `z` can be obtained when `x` is smaller than `y` by element-wise comparison.

`vcmpv_ne: z = (x != y)`, where `z` can be obtained when `x` is not equal to `y` by element-wise comparison.

**Prototype**

```python
class vcmpv(x, y, z)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. FP16 and FP32 are supported.|
|y|Input|Tensor variable|Input `y` vector tensor. FP16 and FP32 are supported.|
|z|Output|Tensor variable|Output vector tensor.|

**Constraints**

The tensors of all input and output data of vector instructions are in the UB space, and their shapes must be the same.

**Example**

```python
from mskpp import vcmpv, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vcmpv(ub_x, ub_y, ub_z)()
```

**Returns**

None

### `vcmpvs_xxx`

**Function**

`vcmpvs_[eq|ge|gt|le|lt|ne]` instruction abstraction. The following six instructions have the same performance.

`vcmpvs_eq: z = (x == y)`, where `z` can be obtained when `x` is equal to scalar stored in `y` by element-wise comparison.

`vcmpvs_ge: z = (x >= y)`, where `z` can be obtained when `x` is greater than or equal to scalar stored in `y` by element-wise comparison.

`vcmpvs_gt: z = (x > y)`, where `z` can be obtained when `x` is greater than scalar stored in `y` by element-wise comparison.

`vcmpvs_le: z = (x <= y)`, where `z` can be obtained when `x` is less than or equal to scalar stored in `y` by element-wise comparison.

`vcmpvs_lt: z = (x < y)`, where `z` can be obtained when `x` is smaller than scalar stored in `y` by element-wise comparison.

`vcmpvs_ne: z = (x != y)`, where `z` can be obtained when `x` is not equal to scalar stored in `y` by element-wise comparison.

**Prototype**

```python
class vcmpvs(x, y, z)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. FP16 and FP32 are supported.|
|y|Input|Tensor variable|Input `y` vector tensor. FP16 and FP32 are supported.|
|z|Output|Tensor variable|Output vector tensor.|

**Constraints**

The tensors of all input and output data of vector instructions are in the UB space, and their shapes must be the same.

**Example**

```python
from mskpp import vcmpvs, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vcmpvs(ub_x, ub_y, ub_z)()
```

**Returns**

None

### `vcopy`

**Function**

`vcopy` instruction abstraction.

Copies tensors at the source address to the destination address.

**Prototype**

```python
class vcopy(x, y)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input vector tensor. int16, int32, uint16, and uint32 are supported.|
|y|Output|Tensor variable|Output vector tensor. int16, int32, uint16, and uint32 are supported.|

**Example**

```python
from mskpp import vcopy, Tensor
ub_x, ub_y = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
ub_x.load(gm_x)
out = vcopy(ub_x, ub_y)()
```

**Returns**

None

### `vcpadd`

**Function**

`vcpadd` instruction abstraction.

Calculates the sum of n and n+1 of the input `x` vector, and writes the result back to y. n is an even index. `reduce_num` controls the output type.

**Prototype**

```python
class vcpadd(x, y, reduce_num)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. fp16 and fp32 are supported.|
|y|Output|Tensor variable|Output `y` vector tensor. fp16 and fp32 are supported.|
|reduce_num|Input|Int|Reduction factor for the shape.|

**Example**

```python
from mskpp import vcpadd, Tensor
ub_x, ub_y = Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vcpadd(ub_x, ub_y, reduce_num)()
```

**Returns**

None

### `vgather`

**Function**

Gathers given input tensors by element to the result tensor based on the offset address tensor provided.

**Prototype**

```python
class vgather(x, y)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. UINT16 and UINT32 are supported.|
|y|Output|Tensor variable|Output `y` vector tensor. UINT16 and UINT32 are supported.|

**Example**

```python
from mskpp import vgather, Tensor
ub_x, ub_y = Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vgather(ub_x, ub_y)()
```

**Returns**

None

### `vgatherb`

**Function**

Gathers a given input tensor to the result tensor based on the offset address tensor provided.

**Prototype**

```python
class vgatherb(x, y)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. UINT16 and UINT32 are supported.|
|y|Output|Tensor variable|Output `y` vector tensor. UINT16 and UINT32 are supported.|

**Example**

```python
from mskpp import vgatherb, Tensor
ub_x, ub_y = Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vgatherb(ub_x, ub_y)()
```

**Returns**

None

### `vlrelu`

**Function**

`vlrelu` instruction abstraction.

If `x` is greater than or equal to 0, `z` = `x`. If `x` is less than 0, `z=x*y`, where `x` is multiplied by scalar `y` by element.

**Prototype**

```python
class vlrelu(x, y, z)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. float16 and float32 are supported.|
|y|Input|Tensor variable|Input `y` scalar. float16 and float32 are supported.|
|z|Output|Tensor variable|Output vector tensor. float16 and float32 are supported.|

**Example**

```python
from mskpp import vlrelu, Tensor
ub_x, ub_z = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
scalar_y = 5  // 5 is the value of scalar y.
ub_x.load(gm_x)
out = vlrelu(ub_x, scalar_y, ub_z)()
```

**Returns**

None

### `vmadd`

**Function**

`vmadd` instruction abstraction.

`z` = `x` × `z` + `y`. Performs multiplication and addition on each element of the two vectors.

**Prototype**

```python
class vmadd(x, y, z)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. float16 and float32 are supported.|
|y|Input|Tensor variable|Input `y` vector tensor. float16 and float32 are supported.|
|z|Output|Tensor variable|Output vector tensor. float16 and float32 are supported.|

**Example**

```python
from mskpp import vmadd, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vmadd(ub_x, ub_y, ub_z)()
```

**Returns**

None

### `vmaddrelu`

**Function**

`vmaddrelu` instruction abstraction.

`z = RELU(x * z + y)`: Performs multiplication and addition on each element of the two vectors, and then performs an MADDRELU operation on each element in the result.

**Prototype**

```python
class vmaddrelu(x, y, z)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. float16 and float32 are supported.|
|y|Input|Tensor variable|Input `y` vector tensor. float16 and float32 are supported.|
|z|Output|Tensor variable|Output vector tensor. float16 and float32 are supported.|

**Example**

```python
from mskpp import vmaddrelu, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vmaddrelu(ub_x, ub_y, ub_z)()
```

**Returns**

None

### `vmaxs`

**Function**

`vmaxs` instruction abstraction.

Compares each element in the vector with a scalar and returns the larger one.

**Prototype**

```python
class vmaxs(x, y, z)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. float16, float32, int16, and int32 are supported.|
|y|Input|Tensor variable|Input scalar. The program does not process this parameter.|
|z|Output|Tensor variable|Output vector tensor. float16, float32, int16, and int32 are supported.|

**Example**

```python
from mskpp import vmaxs, Tensor
ub_x, ub_z = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
ub_x.load(gm_x)
out = vmaxs(ub_x, 5, ub_z)()
```

**Returns**

None

### `vmin`

**Function**

`vmin` instruction abstraction.

Compares each element in two vectors with a scalar and returns the smaller one.

**Prototype**

```python
class vmin(x, y, z)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. float16, float32, int16, and int32 are supported.|
|y|Input|Tensor variable|Input `y` vector tensor. float16, float32, int16, and int32 are supported.|
|z|Output|Tensor variable|Output vector tensor. float16, float32, int16, and int32 are supported.|

**Example**

```python
from mskpp import vmin, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vmin(ub_x, ub_y, ub_z)()
```

**Returns**

None

### `vmins`

**Function**

`vmins` instruction abstraction.

Compares each element in the vector with a scalar and returns the smaller one.

**Prototype**

```python
class vmins(x, y, z)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. float16, float32, int16, and int32 are supported.|
|y|Input|Tensor variable|Input scalar. The program does not process this parameter.|
|z|Output|Tensor variable|Output vector tensor. float16, float32, int16, and int32 are supported.|

**Example**

```python
from mskpp import vmins, Tensor
ub_x, ub_z = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
ub_x.load(gm_x)
out = vmins(ub_x, 5, ub_z)()  // 5 is a scalar value of y.
```

**Returns**

None

### `vmla`

**Function**

`vmla` instruction abstraction.

`z = x * y + z`, where `x` and `y` are multiplied by element, and the multiplication result is added to `z` by element. The output data type can be specified as FP32 by using `if_mix`.

The value can be:

type = f16: f16 = f16 × f16 + f16

type = f32: f32 = f32 × f32 + f32

`if_mix = True`: f32 = f16 × f16 + f32. The `x` and `y` vectors use 64-element f16 data for calculation. The source vector uses only the lower four blocks, and the upper four blocks are ignored. `Xd` is 64-element f32 data with eight blocks, and is used as both the target vector and the third source vector.

**Prototype**

```python
class vmla(x, y, z, if_mix=False)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. FP16 and FP32 are supported.|
|y|Input|Tensor variable|Input `y` vector tensor. FP16 and FP32 are supported.|
|z|Output|Tensor variable|Output vector tensor. FP16 and FP32 are supported.|
|if_mix|Input|Tensor variable|The default value is `False`. If this parameter is set to `True`, the output data type is FP32.|

**Constraints**

The tensors of input and output data of vector instructions are in the UB space.

**Example**

```python
from mskpp import vmla, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vmla(ub_x, ub_y, ub_z)()
```

**Returns**

None

### `vmrgsort`

**Function**

Merges at most four sorted Region Proposal lists into one. The results are sorted in descending order of the `score` fields.

**Prototype**

```python
class vmrgsort(x, y, z)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. FP16 and FP32 are supported.|
|y|Input|Tensor variable|Input `y` vector tensor. UINT64 is supported.|
|z|Output|Tensor variable|Output vector tensor. FP16 and FP32 are supported.|

**Example**

```python
from mskpp import vmrgsort, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vmrgsort(ub_x, ub_y, ub_z)()
```

**Returns**

None

### `vmulconv`

**Function**

`vmulconv` instruction abstraction.

`z = vmulconv(x, y)`, where `x` and `y` are multiplied by element, and the output is quantized.

**Prototype**

```python
class vmulconv(x, y, z, dtype)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. FP16 is supported.|
|y|Input|Tensor variable|Input `y` vector tensor. FP16 is supported.|
|z|Output|Tensor variable|Output vector tensor.|
|dtype|Input|Tensor variable|Input data type, including UINT8 and INT8. The output data type of `z` is determined by `dtype`.|

**Example**

```python
from mskpp import vmulconv, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vmulconv(ub_x, ub_y, ub_z, 'UINT8')()
```

**Returns**

None

### `vnot`

**Function**

`vnot` instruction abstraction.

Performs bitwise NOT on input vectors. Each vector has 8 × 256 bits.

**Prototype**

```python
class vnot(x, y)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. INT16 and UINT16 are supported.|
|y|Output|Tensor variable|Output `y` vector tensor. INT16 and UINT16 are supported.|

**Example**

```python
from mskpp import vnot, Tensor
ub_x, ub_y = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
ub_x.load(gm_x)
out = vnot(ub_x, ub_y)()
```

**Constraints**

This instruction supports only the common mask mode and counter mode.

**Returns**

None

### `vor`

**Function**

`vor` instruction abstraction.

Performs bitwise OR on input vectors. Each vector has 8 × 256 bits.

**Prototype**

```python
class vor(x, y, z)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. INT16 and UINT16 are supported.|
|y|Input|Tensor variable|Input `y` vector tensor. INT16 and UINT16 are supported.|
|z|Output|Tensor variable|Output `z` vector tensor. INT16 and UINT16 are supported.|

**Example**

```python
from mskpp import vor, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x,gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vor(ub_x, ub_y, ub_z)()
```

**Constraints**

This instruction supports only the common mask mode and counter mode.

**Returns**

None

### `vrec`

**Function**

`vrec` instruction abstraction.

Performs floating-point reciprocal estimation and finds an approximate reciprocal for each vector.

**Prototype**

```python
class vrec(x, y)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. FP16 and FP32 are supported.|
|y|Output|Tensor variable|Output `y` vector tensor. FP16 and FP32 are supported.|

**Example**

```python
from mskpp import vrec, Tensor
ub_x, ub_y = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
ub_x.load(gm_x)
out=vrec(ub_x, ub_y)()
```

**Returns**

None

### `vreduce`

**Function**

`vreduce` instruction abstraction.

Determines which elements of the `x` vector are to be stored in the `z` vector based on the mask data of the input `y` vector. Because the tensor in msKPP lacks actual elements, the `reserve_num` parameter is added to determine the shape of the `z` output.

**Prototype**

```python
class vreduce(x, y, z, reserve_num)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. UINT16 and UINT32 are supported.|
|y|Input|Tensor variable|Input `y` vector tensor. UINT16 and UINT32 are supported.|
|z|Output|Tensor variable|Output `z` vector tensor. UINT16 and UINT32 are supported.|
|reserve_num|Input|Int|Number of output elements.|

**Example**

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

**Returns**

None

### `vreducev2`

**Function**

`vreducev2` instruction abstraction.

Determines which block-level elements of the `x` vector are to be stored in the `z` vector based on the mask data of the input `y` vector. Because the tensor in msKPP lacks related concepts, the `reserve_num` parameter is added to determine the shape of the `z` output.

**Prototype**

```python
class vreducev2(x, y, z, reserve_num)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. UINT16 and UINT32 are supported.|
|y|Input|Tensor variable|Input `y` vector tensor. UINT16 and UINT32 are supported.|
|z|Output|Tensor variable|Output `z` vector tensor. UINT16 and UINT32 are supported.|
|reserve_num|Input|Int|Number of output elements.|

**Example**

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

**Returns**

None

### `vrelu`

**Function**

`vrelu` instruction abstraction.

Performs the relu operation on each element, which takes 0 if the element is less than 0, and takes the element itself if it is greater than or equal to 0.

**Prototype**

```python
class vrelu(x, y)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. float16, float32, and int32 are supported.|
|y|Output|Tensor variable|Output vector tensor. float16, float32, and int32 are supported.|

**Example**

```python
from mskpp import vrelu, Tensor
ub_x, ub_y = Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vrelu(ub_x, ub_y)()
```

**Returns**

None

### `vrsqrt`

**Function**

`vrsqrt` instruction abstraction.

Calculates the reciprocal square root of a floating point number.

**Prototype**

```python
class vrsqrt(x, y)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. float16 and float32 are supported.|
|y|Output|Tensor variable|Output vector tensor. float16 and float32 are supported.|

**Example**

```python
from mskpp import vrsqrt, Tensor
ub_x, ub_y = Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vrsqrt(ub_x, ub_y)()
```

**Returns**

None

### `vsel`

**Function**

`vsel` instruction abstraction.

This function is usually used in conjunction with `vcmp`, which selects an element in the corresponding positions of `x` and `y` based on the obtained `cmp_mask`.

**Prototype**

```python
class vsel(x, y, z)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. FP16, FP32, INT16, and INT32 are supported.|
|y|Input|Tensor variable|Input `y` vector tensor. FP16, FP32, INT16, and INT32 are supported.|
|z|Output|Tensor variable|Output vector tensor. FP16, FP32, INT16, and INT32 are supported.|

**Example**

```python
from mskpp import vsel, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vsel(ub_x, ub_y, ub_z)()
```

**Returns**

None

### `vshl`

**Function**

`vshl` instruction abstraction.

Performs logical left shift or arithmetic left shift based on the input type.

**Prototype**

```python
class vshl(x, y)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. UINT16, UINT32, INT16, and INT32 are supported.|
|y|Output|Tensor variable|Output `y` vector tensor. UINT16, UINT32, INT16, and INT32 are supported.|

**Example**

```python
from mskpp import vshl, Tensor
ub_x, ub_z = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
ub_x.load(gm_x)
out = vshl(ub_x, ub_z)()
```

**Returns**

None

### `vshr`

**Function**

`vshr` instruction abstraction.

Performs logical right shift or arithmetic right shift based on the input type.

**Prototype**

```python
class vshr(x, y)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. UINT16, UINT32, INT16, and INT32 are supported.|
|y|Output|Tensor variable|Output `y` vector tensor. UINT16, UINT32, INT16, and INT32 are supported.|

**Example**

```python
from mskpp import vshr, Tensor
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vshr(ub_x, ub_y)()
```

**Returns**

None

### `vsqrt`

**Function**

`vsqrt` instruction abstraction.

`y = √x`, which takes the square root of `x` by element.

**Prototype**

```python
class vsqrt(x, y)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. float16 and float32 are supported.|
|y|Output|Tensor variable|Output `y` vector tensor. float16 and float32 are supported.|

**Example**

```python
from mskpp import vsqrt, Tensor
ub_x, ub_z = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
ub_x.load(gm_x)
out = vsqrt(ub_x, ub_y)()
```

**Constraints**

The input value must be a positive number. Otherwise, the result is unknown and an exception occurs.

**Returns**

None

### `vsubrelu`

**Function**

`vsubrelu` instruction abstraction.

`z = vsubrelu(x, y)`, where the relu value is calculated after `x` is subtracted by `y` by element.

**Prototype**

```python
class vsubrelu (x, y, z)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. float16 and float32 are supported.|
|y|Input|Tensor variable|Input `y` vector tensor. float16 and float32 are supported.|
|z|Output|Tensor variable|Output vector tensor. float16 and float32 are supported.|

**Example**

```python
from mskpp import vsubrelu, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vsubrelu(ub_x, ub_y, ub_z)()
```

**Returns**

None

### `vsubreluconv`

**Function**

`vsubreluconv` instruction abstraction.

`z = vsubreluconv(x, y)`, where `x` and `y` are subtracted by element, the relu value is calculated, and the output is quantized.

The following conversion types are supported: FP16->INT8, FP32->FP16, and INT16->INT8.

**Prototype**

```python
class vsubreluconv(x, y, z)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. FP16, FP32, and INT16 are supported.|
|y|Input|Tensor variable|Input `y` vector tensor. FP16, FP32, and INT16 are supported.|
|z|Output|Tensor variable|Output vector tensor. FP16 and INT8 are supported.|

**Example**

```python
from mskpp import vsubreluconv, Tensor
ub_x, ub_y, ub_z = Tensor("UB"), Tensor("UB"), Tensor("UB")
gm_x, gm_y = Tensor("GM"), Tensor("GM")
ub_x.load(gm_x)
ub_y.load(gm_y)
out = vsubreluconv(ub_x, ub_y, ub_z)()
```

**Returns**

None

### `vtranspose`

**Function**

`vtranspose` instruction abstraction.

Transposes a 16 × 16 matrix starting from the input address `x` (32-byte aligned). Each element has 16 bits. The result is output to `y`. The input and output are continuous 512-byte storage spaces.

**Prototype**

```python
class vtranspose (x, y)
```

**Parameter Description**

|Parameter|Input/Output|Data Type|Description|
|--|--|--|--|
|x|Input|Tensor variable|Input `x` vector tensor. INT16 is supported.|
|y|Output|Tensor variable|Output vector tensor. INT16 is supported.|

**Example**

```python
from mskpp import vtranspose, Tensor
ub_x, ub_y = Tensor("UB"), Tensor("UB")
gm_x = Tensor("GM")
ub_x.load(gm_x)
out = vtranspose(ub_x, ub_y)()
```

**Returns**

None
