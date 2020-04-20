#include <pybind11\pybind11.h>
#include "provider.hpp"

namespace py = pybind11;

PYBIND11_MODULE(user, m)
{
    // m.def("reportPet", [&](py::object arg) {
    //     auto pet = py::module::import("provider").attr("Pet");
    //     if (arg.is(pet))
    //     {
    //         py::print(formatPet(arg.cast<Pet>()));
    //     }
    //     else
    //     {
    //         py::print("invalid arg");
    //     }
    // });
    m.def("reportPet", [](Pet pet) {
        py::print(formatPet(pet));
    });
}