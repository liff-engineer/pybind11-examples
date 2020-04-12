#include <pybind11\embed.h>

PYBIND11_EMBEDDED_MODULE(fast_calc, m)
{
    m.def("add", [](int i, int j) {
        return i + j;
    });
}

int main()
{
    pybind11::scoped_interpreter guard{};

    //use python module
    pybind11::module sys = pybind11::module::import("sys");
    pybind11::print(sys.attr("path"));

    //use embed module
    auto fast_calc = pybind11::module::import("fast_calc");
    auto result = fast_calc.attr("add")(1, 2).cast<int>();
    pybind11::print("\nembed module calc result:");
    pybind11::print(result);

    //embed interpreter
    pybind11::exec(R"(
        kwargs = dict(name="IS",number=667)
        message = "Shoot {name} with id {number}".format(**kwargs)
        print(message)
    )");
    return 0;
}