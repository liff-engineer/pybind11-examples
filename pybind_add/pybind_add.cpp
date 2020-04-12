#include <pybind11\pybind11.h>

int add_function(int i, int j)
{
    return i + j;
}

PYBIND11_MODULE(pybind_add, m)
{
    m.doc() = "pybind11 add example plugin";
    m.def("add_function", &add_function, "Adds two number");
    m.def(
        "add_lambda", [](int i, int j) { return i + j; }, "Adds two numbers");
}