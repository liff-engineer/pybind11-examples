# 类型提示与pybind11



python的类型提示写法参见[PEP 484 -- Type Hints](https://www.python.org/dev/peps/pep-0484/)



由于pybind11生成的是二进制的包,在使用Visual Studio Code等IDE编写python代码时,导入这些包时语法提示很多情况下不能正常工作,因而可以跟随二进制包提供`.pyi`文件,该文件包含导出的各种定义、声明与文档,能够在IDE支持的情况下得到类似于静态类型语言的语法提示,从而提高工作效率.

