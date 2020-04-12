# pybind11 examples

根据[Mixing C++ & Python II: Pybind11](https://www.slideshare.net/corehard_by/mixing-c-python-ii-pybind11)实现.

## 环境要求

- IDE: Visual Studio Code ,包含 C++、Python、CMake 所需插件
- python
- 编译器:MSVC 2019
- CMake 3.15 及以上版本

## 构建及运行方式

使用 Visual Studio Code 打开示例目录,在`build\<config>`下生成结果,然后命令行切换到目标目录,启动`python`解释器,按照常规 python 模块方式加载.具体运行参见示例中的说明.

## 样例顺序

1. `pybind_add`:演示如何创建一个 Python 接口模块,并展示函数导出时的函数指针以及 lambda 表达式两种方式.

2. `task`:展示如何导出类定义

3. `pybind_functions`:展示关于函数的一些详细用法

4. `embed`:展示如何将 Python 的解释器嵌入 C++应用程序
