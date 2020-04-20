from typing import TypeVar, Iterable, Tuple, Callable


def greeting(name: str) -> str:
    # 基本写法
    return 'Hello '+name


# 类型别名
Url = str


def retry(url: Url, retry_count: int) -> None: ...

# 比较复杂的类型别名示例


T = TypeVar('T', int, float, complex)
Vector = Iterable[Tuple[T, T]]


def inproduct(v: Vector[T]) -> T:
    return sum(x*y for x, y in v)


def dilate(v: Vector[T], scale: T) -> Vector[T]:
    return ((x*slice, y*slice) for x, y in v)

# 可调用对象


def feeder(get_next_item: Callable[[], str]) -> None:
    pass


def async_query(on_success: Callable[[int], None],
                on_error: Callable[[int, Exception], None]) -> None:
    pass
