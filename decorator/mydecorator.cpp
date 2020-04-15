#include <pybind11\pybind11.h>
#include <string>
#include <pybind11\stl.h>

namespace py = pybind11;

struct example
{
    std::string name;
};

PYBIND11_MODULE(mydecorator, m)
{
    py::object singledispatch = py::module::import("functools").attr("singledispatch");
    py::object string_ = py::module::import("builtins").attr("str");

    m.def(
        "fun", [](py::object arg, bool verbose = false) {
            if (verbose)
            {
                py::print("Let me just say", py::arg("end") = " ");
            }
            py::print(arg);
        },
        py::arg("arg"), py::arg("verbose") = false);

    m.attr("fun") = singledispatch(m.attr("fun"));

    py::class_<example> ex(m, "example");
    ex.def(py::init<>());
    ex.def(py::init<std::string>(), py::arg("name"));
    ex.def_readwrite("name", &example::name);
    ex.def("__repr__", [](const example &ex) -> std::string {
        return ex.name;
    });

    m.def(
        "fun_example", [](example arg, bool verbose = false) {
            if (verbose)
            {
                py::print("get example", py::arg("end") = " ");
            }
            py::print(arg);
        },
        py::arg("arg"), py::arg("verbose") = false);
    m.def(
        "fun_str", [](py::str arg, bool verbose = false) {
            if (verbose)
            {
                py::print("get string", py::arg("end") = " ");
            }
            py::print(arg);
        },
        py::arg("arg"), py::arg("verbose") = false);

    //decorator
    auto fun = m.attr("fun");
    auto fun_register = fun.attr("register");
    m.attr("fun_example") = fun_register(m.attr("example"))(m.attr("fun_example"));
    m.attr("fun_str") = fun_register(string_)(m.attr("fun_str"));
}