#include <string>
#include <functional>
#include <pybind11\pybind11.h>
#include <pybind11\functional.h>

int func_arg(const std::function<int(int)> &f)
{
    return f(10);
}

std::function<int(int)> func_ret(const std::function<int(int)> &f)
{
    return [f](int i) {
        return f(i) + 1;
    };
}

pybind11::cpp_function func_cpp()
{
    return pybind11::cpp_function(
        [](int i) {
            return i + 1;
        },
        pybind11::arg("number"));
}

enum class TankType
{
    HEAVY,
    LIGHT
};

PYBIND11_MODULE(pybind_functions, m)
{
    m.def(
        "shoot", [](const std::string &name) {
            pybind11::print("Didn't penetrate the armor of " + name + ".");
        },
        "Shoot a tank.", pybind11::arg("name"));
    m.def(
        "shoot_default_argument", [](const std::string &name, unsigned times) {
            if (times > 3)
            {
                pybind11::print("Kill " + name + ".");
            }
            else
            {
                pybind11::print("Didn't penetrate " + name + ".");
            }
        },
        "Shoot a tank.", pybind11::arg("name"), pybind11::arg("times") = 1);

    m.def("count_args", [](pybind11::args a, pybind11::kwargs kw) {
        pybind11::print(a.size(), "args,", kw.size(), "kwargs");
    });

    m.def("count_strings", [](pybind11::list list) {
        int n = 0;
        for (auto item : list)
        {
            if (pybind11::isinstance<pybind11::str>(item))
            {
                ++n;
            }
        }
        return n;
    });

    m.def("go_to", [](int x, int y) {
        return "go_to int";
    });
    m.def("go_to", [](double x, double y) {
        return "go_to double";
    });

    m.def("func_arg", &func_arg);
    m.def("func_ret", &func_ret);
    m.def("func_cpp", &func_cpp);

    pybind11::enum_<TankType>(m, "TankType")
        .value("HEAVY", TankType::HEAVY)
        .value("LIGHT", TankType::LIGHT)
        .export_values();
}