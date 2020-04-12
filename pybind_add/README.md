# 运行方式

在`build\<config>`下启动`python`解释器.

1. 导入`pybind_add`:

   ```python
   import pybind_add
   ```

2. 执行`add_function`:

   ```python
   add = pybind_add.add_function
   add(2,5)
   ```

   上述示例输出`7`

3. 查看`add_function`帮助文档:

   ```python
   help(add)
   ```

4. 输入错误的参数类型试试:

   ```python
   add(4.5,4.5)
   ```

5. 切换成`add_lambda`重复试试:

   ```python
   add = pybind_add.add_lambda
   add(2,5)
   help(add)
   add(4.5,4.5)
   ```
