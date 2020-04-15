from mydecorator import fun,example


@fun.register(int)
def _(arg, verbose=False):
    if verbose:
        print("Strength in numbers, eh?", end=" ")
    print(arg)


@fun.register(list)
def _(arg, verbose=False):
    if verbose:
        print("Enumerate this:")
    for i, e in enumerate(arg):
        print(i, e)


def nothing(arg, verbose=False):
    print("Nothing.")


fun.register(type(None), nothing)


@fun.register(float)
def fun_num(arg, verbose=False):
    if verbose:
        print("Half of your number:", end=" ")
    print(arg/2)


fun("Hello,world")
fun("test.", verbose=True)
fun(42, verbose=True)
fun(['spam', 'spam', 'eggs', 'spam'], verbose=True)
fun(None)
fun(1.23)
ex = example()
ex.name="Lee"
fun(example(name="Lee"),verbose=True)

# 输出函数集合包含的所有类型
print(fun.registry.keys())

# 根据类型从函数集合中拿到函数并执行
fun.registry[float](3.14, verbose=True)
