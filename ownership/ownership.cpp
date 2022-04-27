#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <iostream>

// 在Python端派生的接口,其生命周期如何控制?
// 它无法通过move到C++端,将生命周期交给C++端管理
// 而如果派生类需要将其注册到C++端,则Python端是不会再进行管理的,该对象就可能立即被gc释放
// 因而可以通过py::nodelete避免Python端释放,py::nodelete要求析构只能走C++端
// 可以构造完之后注册到C++端,C++端接收时将其转换为智能指针,来管理生命周期

//https://stackoverflow.com/questions/49010233/pybind11-transfer-class-ownership-to-c-on-construct?rq=1
//https://pybind11.readthedocs.io/en/stable/advanced/classes.html#non-public-destructors
class IActor {
public:
	virtual ~IActor() {
		std::cout << "~IActor()\n";
	}

	virtual void Launch() = 0;
	//{
	//	std::cout << "IActor::Launch()\n";
	//}
};

class Actor {
	IActor* obj{};
public:
	Actor() {
		std::cout << "Actor()\n";
	}

	virtual ~Actor() {
		::fprintf(stderr, "~Actor()");
		delete obj;
	}

	virtual IActor* Alloc() = 0;
	//{
	//	return new IActor;
	//}

	void What() {
		obj = Alloc();
		obj->Launch();
	}
};

namespace py = pybind11;

class PyIActor :public IActor {
public:
	using IActor::IActor;

	void Launch() override {
		PYBIND11_OVERLOAD_PURE(
			void, 
			IActor,
			Launch
		);
	}
};

class PyActor :public Actor {
public:
	using Actor::Actor;

	IActor* Alloc() override {
		PYBIND11_OVERLOAD_PURE(
			IActor*,
			Actor, 
			Alloc
		);
	}
};

#include <list>
#include <unordered_map>
std::unordered_map<IActor*, std::unique_ptr<IActor>>
actors;

void Test(IActor* actor) {
	if (actor) {
		actor->Launch();
		actors[actor] = std::unique_ptr<IActor>(actor);
	}
}

PYBIND11_MODULE(TestModule, m)
{
	m.def("Test", Test);
	py::class_<IActor, PyIActor, std::unique_ptr<IActor, py::nodelete>>(m, "IActor")
		.def(py::init<>())
		.def("Launch", &IActor::Launch);
	py::class_<Actor, PyActor>(m, "Actor")
		.def(py::init<>())
		.def("What", &Actor::What)
		.def("Alloc", &Actor::Alloc, py::return_value_policy::reference_internal);
}