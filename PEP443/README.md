# [PEP 443 Single-dispatch generic functions](https://www.python.org/dev/peps/pep-0443/)

在 C++中我们可以使用模板以及`tag_dispatch`来实现根据类型不同执行不同的函数内容,这些特性是否能够在 Python 中使用,以此来保证 pybind11 提供出来的 python 接口和 C++接口保持一致.

**PEP 433**算是一种方案.

## 一个示例

参见`example.py`
