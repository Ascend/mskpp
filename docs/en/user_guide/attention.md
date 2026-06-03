# **Constraints and Precautions for MindStudio Kernel Performance Prediction**

- When using the msKPP library to implement operator simulation, pay attention to the following points:
    + Before modeling a simulation operator, import tensors, chips, and instructions (in lowercase) required for operator implementation from the msKPP library.
    + Refer to the sample `sample_vadd.py` or `sample_mmad.py` in the project. Use the `with` statement to enable the entry of the operator implementation code. The `enable_trace` and `enable_metrics` APIs can enable the trace dotting and instruction statistics functions.
- Ensure that the input data is reliable and secure during secondary development.
