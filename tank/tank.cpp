#include <string>
#include <pybind11\pybind11.h>

#ifdef has_operator
#include <pybind11\operators.h>
#endif
constexpr auto INITIAL_LIVES = 3u;

struct Tank_A
{
    std::string name;
    unsigned lives;
    int x;
    int y;
};

struct Tank_B
{
    std::string name;
    unsigned lives;
    int x;
    int y;
};

struct Tank_C
{
    std::string name;
    unsigned lives;
    int x;
    int y;

    Tank_C(std::string name_, unsigned lives_ = INITIAL_LIVES, int x_ = 0, int y_ = 0)
        : name{name_}, lives{lives_}, x{x_}, y{y_}
    {
    }

    Tank_C() : Tank_C("IS") {}
};

struct Tank_D
{
    std::string name;
    unsigned lives;
    int x;
    int y;

    Tank_D(std::string name_, unsigned lives_ = INITIAL_LIVES, int x_ = 0, int y_ = 0)
        : name{name_}, lives{lives_}, x{x_}, y{y_}
    {
    }

    Tank_D() : Tank_D("IS") {}

    bool is_dead() const { return lives == 0u; }

    std::string to_string() const
    {
        return "<" + name + ":" + std::to_string(lives) +
               "[" + std::to_string(x) + ", " + std::to_string(y) + "]>";
    }
};

struct Tank
{
    std::string name;
    unsigned lives;
    int x;
    int y;

    Tank(std::string name_, unsigned lives_ = INITIAL_LIVES, int x_ = 0, int y_ = 0)
        : name{name_}, lives{lives_}, x{x_}, y{y_}
    {
    }

    Tank() : Tank("IS") {}

    bool is_dead() const { return lives == 0u; }

    std::string to_string() const
    {
        return "<" + name + ":" + std::to_string(lives) +
               "[" + std::to_string(x) + ", " + std::to_string(y) + "]>";
    }
};

bool operator==(const Tank &lhs, const Tank &rhs)
{
    return lhs.name == rhs.name;
}

PYBIND11_MODULE(tank, m)
{
    pybind11::class_<Tank_A>(m, "TankA")
        .def_readonly("name", &Tank_A::name)
        .def_readonly("lives", &Tank_A::lives)
        .def_readonly("x", &Tank_A::x)
        .def_readonly("y", &Tank_A::y);

    pybind11::class_<Tank_B>(m, "TankB")
        .def_readonly("name", &Tank_B::name)
        .def_readwrite("lives", &Tank_B::lives)
        .def_readwrite("x", &Tank_B::x)
        .def_readwrite("y", &Tank_B::y);

    pybind11::class_<Tank_C>(m, "TankC")
        .def(pybind11::init<>())
        .def(pybind11::init<std::string>())
        .def(pybind11::init<std::string, unsigned>())
        .def(pybind11::init<std::string, unsigned, int>())
        .def(pybind11::init<std::string, unsigned, int, int>())
        .def_readonly("name", &Tank_C::name)
        .def_readonly("lives", &Tank_C::lives)
        .def_readonly("x", &Tank_C::x)
        .def_readonly("y", &Tank_C::y);

    pybind11::class_<Tank_D>(m, "TankD")
        .def(pybind11::init<>())
        .def(pybind11::init<std::string>())
        .def(pybind11::init<std::string, unsigned>())
        .def(pybind11::init<std::string, unsigned, int>())
        .def(pybind11::init<std::string, unsigned, int, int>())
        .def_readonly("name", &Tank_D::name)
        .def_readonly("lives", &Tank_D::lives)
        .def_readonly("x", &Tank_D::x)
        .def_readonly("y", &Tank_D::y)
        .def_property_readonly("is_dead", &Tank_D::is_dead)
        .def("__repr__", &Tank_D::to_string);

    pybind11::class_<Tank>(m, "Tank")
        .def(pybind11::init<>())
        .def(pybind11::init<std::string>())
        .def(pybind11::init<std::string, unsigned>())
        .def(pybind11::init<std::string, unsigned, int>())
        .def(pybind11::init<std::string, unsigned, int, int>())
        .def_readonly("name", &Tank::name)
        .def_readonly("lives", &Tank::lives)
        .def_readonly("x", &Tank::x)
        .def_readonly("y", &Tank::y)
        .def_property_readonly("is_dead", &Tank::is_dead)
#ifdef has_operator
        .def(pybind11::self == pybind11::self)
#else
        .def(
            "__eq__", [](const Tank &lhs, const Tank &rhs) { return lhs == rhs; }, pybind11::is_operator())
#endif
        .def("__repr__", &Tank::to_string)
        .def(pybind11::pickle(
            [](const Tank &o) {
                return pybind11::make_tuple(o.name, o.lives, o.x, o.y);
            },
            [](pybind11::tuple t) {
                if (t.size() != 4)
                    throw std::runtime_error("Invalid data!");
                Tank tank(t[0].cast<std::string>(),
                          t[1].cast<unsigned>(),
                          t[2].cast<int>(),
                          t[3].cast<int>());
                return tank;
            }));

    // m.def(
    //     "shoot", [](const std::string &name) {
    //         pybind11::print("Didn;t penetrate the armor of " + name + ".");
    //     },
    //     "Shoot a tank.", pybind11::arg("name"));
}
