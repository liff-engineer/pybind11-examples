# 样例释义

样例展示了如何为`class`提供构造函数,成员变量操作,成员函数定义,比较函数,转换为字符串`__repr__`,以及序列化支持`pickle`.

在`build\<config>`目录下启动`python`解释器:

1. 从模块导入`Tank`:

   ```python
   from tank import Tank
   ```

2. 使用默认构造函数构造:

   ```python
   Tank()
   ```

3. 使用构造函数构造:

   ```python
   is2 = Tank("IS-2")
   is2.name
   ```

4. 使用属性:

   ```python
   is2.is_dead
   ```

5. 比较:

   ```python
   is2 == Tank()
   ```
