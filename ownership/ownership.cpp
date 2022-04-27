#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <iostream>

// ��Python�������Ľӿ�,������������ο���?
// ���޷�ͨ��move��C++��,���������ڽ���C++�˹���
// �������������Ҫ����ע�ᵽC++��,��Python���ǲ����ٽ��й����,�ö���Ϳ���������gc�ͷ�
// �������ͨ��py::nodelete����Python���ͷ�,py::nodeleteҪ������ֻ����C++��
// ���Թ�����֮��ע�ᵽC++��,C++�˽���ʱ����ת��Ϊ����ָ��,��������������

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