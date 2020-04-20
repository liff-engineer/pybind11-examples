#include <pybind11\pybind11.h>

namespace py = pybind11;

enum Kind
{
    Dog = 0,
    Cat
};

struct Pet
{
    Pet(const std::string &name, Kind type) : name(name), type(type) {}

    std::string name;
    Kind type;
};

PYBIND11_MODULE(mytype, m)
{
    py::class_<Pet> pet(m, "Pet");

    pet.def(py::init<const std::string &, Kind>())
        .def_readwrite("name", &Pet::name)
        .def_readwrite("type", &Pet::type);

    py::enum_<Kind>(m, "Kind")
        .value("Dog", Kind::Dog)
        .value("Cat", Kind::Cat)
        .export_values();
}