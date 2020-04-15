# pybind11 与 python 修饰器

在 Python 中支持`decorator`,即修饰器模式,既可以用来修饰函数,也可以用来修饰类.这里展示如何利用 pybind11 提供修饰器和应用修饰器.

## 背景知识

首先请阅读一下[PEP443](https://www.python.org/dev/peps/pep-0443/),下述示例均取自其中.

在 pybind11 中导入包/模块然后利用其中的类和函数可以通过如下方式:

```python
from functools import singledispatch
```

```C++
py::object singledispatch = py::module::import("functools").attr("singledispatch");
```

从中我们可以看到,由于 Python 中都是对象,包和模块虽然特殊也不例外,导入的模块`functools`自身是个`pybind11::module`,继承自`pybind11::object`,访问类和函数对象是通过`attr`方法,也可以用来修改.

## 修饰器的 python"实现"

修饰器本质是对对象进行了包裹,即如下语法:

```python
@singledispatch
def fun(arg, verbose=False):
    if verbose:
        print("Let me just say,", end=" ")
    print(arg)
```

则是魔改了`fun`对象,在 pybind11 中写法如下:

```C++
pybind11::module m;//一般是从PYBIND11_MODULE声明得到

m.def("fun",...);//通过pybind11注册fun函数对象

fun = m.attr("fun");//从m获取fun函数对象
m.attr("fun")=singledispatch(fun);//使用singledispatch包裹fun
```

## 类的修饰器

类的写法与函数差不多,这里可参考[https://github.com/pybind/pybind11/issues/1798](https://github.com/pybind/pybind11/issues/1798).

如果定义的修饰器带一些信息,譬如:

```python
def my_decorator(x):
    pass

@my_decorator(x)
class MyClass:...
```

这时的写法为:

```C++
auto MyClass = m.attr("MyClass");
auto my_decorator = m.attr("my_decorator");
auto x = m.attr("x");
m.attr("MyClass") = my_decorator(x)(MyClass);
```

## 样例

样例中展示了如何使用修饰器,在`build\<config>`上构建出`mydecorator`模块,然后将`funUser.py`复制到输出目录,然后执行:

```python
python funUser.py
```
