# MindStudio Kernel Performance Prediction 工具限制与注意事项

- 使用msKPP库实现算子仿真，注意事项包括：
    + 实现模拟算子建模前，需要从msKPP库导入Tensor, Chip, 以及算子实现所必要的指令（统一以小写命名）。
    + 参照工程中的样例`sample_vadd.py`或`sample_mmad.py`，以with语句开启算子实现代码的入口，enable_trace和enable_metrics两个接口可使能trace打点图和指令统计功能。
- 二次开发请保证输入数据可信安全。
