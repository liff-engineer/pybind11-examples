# 跨模块定义与pybind11



通常C++实现导出python接口时不会仅仅导出成一个模块,这就导致多个模块之间共享定义存在一些问题.示例展示了在多个模块使用同一类型定义的实现方式.



使用示例如下:

```python
from provider import Pet
from user import reportPet

reportPet(Pet('mycat'))
```

