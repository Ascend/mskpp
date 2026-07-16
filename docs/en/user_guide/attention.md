# Constraints and Precautions for MindStudio Kernel Performance Prediction

## Development Constraints

- When using the msKPP library to implement operator simulation, pay attention to the following points:
    - Before modeling a simulation operator, import `Tensor`, `Chip`, and instructions (in lowercase) required for operator implementation from the msKPP library.
    - Refer to the sample `sample_vadd.py` or `sample_mmad.py` in the project. Use the `with` statement to enable the entry of the operator implementation code. The `enable_trace` and `enable_metrics` APIs can enable the trace dotting and instruction statistics functions.

## Runtime Constraints

- Performance modeling results depend on time estimation based on input/output scales. No actual computation is performed, and the results are for peak performance reference only.
- To generate the instruction proportion pie chart (`instruction_cycle_consumption.html`), the third-party Python library plotly must be installed in advance:

    ```shell
    pip3 install plotly
    ```

## Security Precautions

- Ensure that the input data is reliable and secure during secondary development.
- The tool involves dynamic Python module loading during runtime. Ensure that dependency libraries in the runtime environment are from trusted sources to avoid arbitrary code injection risks.
