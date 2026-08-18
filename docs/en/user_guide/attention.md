# Constraints and Precautions for MindStudio Kernel Performance Prediction

## Development Constraints

- When using the msKPP library to implement operator simulation, pay attention to the following points:
    - Before modeling a simulation operator, import tensors, chips, and instructions (in lowercase) required for operator implementation from the msKPP library.
    - Refer to the sample `sample_vadd.py` or `sample_mmad.py` in the project. Use the `with` statement to enable the entry of the operator implementation code. The `enable_trace` and `enable_metrics` APIs can enable the trace dotting and instruction statistics functions.

## Runtime Constraints

- The performance modeling result depends on the estimated time based on the input/output scale. No real computation is performed, and the result serves only as a reference for the upper performance limit.
- To generate the instruction proportion pie chart (`instruction_cycle_consumption.html`), install the third-party Python library `plotly` in advance:

    ```shell
    pip3 install plotly
    ```

## Security Precautions

- Ensure that the input data is reliable and secure during secondary development.
- The tool dynamically loads Python modules at runtime. Ensure that the dependent libraries in the running environment come from trusted sources to avoid the risk of arbitrary code injection.
