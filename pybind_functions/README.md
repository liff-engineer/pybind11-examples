# 样例释义

在`build\<config>`目录启动`python`解释器,并通过如下方式导入所有定义:

```python
from pybind_functions import *
```

## 文档,参数名及默认值

1. 查阅文档

   ```python
   help(shoot)
   ```

2. 执行函数

   ```python
   shoot("IS")
   shoot(name="IS1")
   ```

3. 执行带默认值的函数

```python
shoot_default_argument("IS")
shoot_default_argument("IS1",4)
```

## 可变参数及命名参数

```python
count_args(14,10,2017,corehard='autumn')
```

## Python 对象作为参数

```python
count_strings(['IS-2','IS',1,3.14,"IS-7"])
```

## 函数重载

```python
go_to(25,4)
go_to(3.14,3.14)
```

## 回调

```python
def square(i):
    return i*i

func_arg(square)
square_plus_1 = func_ret(square)
square_plus_1(4)
plus_1 = func_cpp()
plus_1(number=43)
```

## 枚举

```python
help(TankType)
```
