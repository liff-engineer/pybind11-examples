# 样例释义

目前的`setup.py`使用了 Visual Studio 2019,在当前目录执行:

```bat
python setup.py bdist_wheel
```

则会在`dist`目录下生成`.whl`二进制包.通过`pip install`安装即可.

可以在`build\lib*`目录下找到构建完成的原始打包内容,用来验证可用性、正确性.
