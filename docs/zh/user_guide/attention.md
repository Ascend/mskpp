# MindStudio Kernel Performance Prediction 工具限制与注意事项

## 开发约束

- 使用 msKPP 库实现算子仿真的注意事项：
    - 实现模拟算子建模前，需要从 msKPP 库导入 Tensor、Chip，以及算子实现所必要的指令（统一以小写命名）。
    - 参照工程中的样例 `sample_vadd.py` 或 `sample_mmad.py`，以 `with` 语句开启算子实现代码的入口。`enable_trace` 和 `enable_metrics` 两个接口可使能 trace 打点图和指令统计功能。

## 运行约束

- 性能建模结果依赖于输入/输出规模的估时，不执行真实计算，仅作为性能上限参考。
- 生成指令占比饼图（`instruction_cycle_consumption.html`）需要预先安装第三方 Python 库 plotly：

    ```shell
    pip3 install plotly
    ```

## 安全注意事项

- 二次开发时，请保证输入数据可信安全。
- 工具运行过程中涉及 Python 动态加载模块，请确保运行环境中的依赖库来源可信，避免任意代码注入风险。
