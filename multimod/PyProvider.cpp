#include <pybind11\pybind11.h>
#include "provider.hpp"

namespace py = pybind11;

PYBIND11_MODULE(provider, m)
{
    py::class_<Pet>(m, "Pet")
        .def(py::init<const std::string &>())
        .def("setName", &Pet::setName)
        .def("getName", &Pet::getName);
}