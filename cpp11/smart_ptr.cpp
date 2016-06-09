#include <memory>
#include <iostream>

class A {
public:
	A(const int i = 10) : v (i) {
		return ;
	}
	virtual ~A(){
	}
	int v;
};

class B : public A {
public:
	B() : A(1), x(2) {
		return ;
	}
	~B() {
		return ;
	}
	int x;
};
class C {
public:
	C() {
		this->a = std::make_shared<B>();
	}

	~C() {
		std::cerr<<a->v<<" "<<std::dynamic_pointer_cast<B>(a)->x<<std::endl;
	}
	std::shared_ptr<A> a;
};

int main () {
	C c;


	return 0;
}
