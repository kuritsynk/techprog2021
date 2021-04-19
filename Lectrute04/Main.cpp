#include <iostream>

using namespace std;

class A {

public: // для демонстрации адреса поля

	int a;

public:
	A(int a) : a(a) {}

	int getA() {
		return a;
	}

	void print() {
		cout << "a=" << a << endl;
	}

};


void foo(A* ptr) {
	if (ptr->getA() > 0) {
		ptr->print();
	}
}

class B : public A {

public: // для демонстрации адреса поля

	int b;

public:

	B(int a, int b) : A(a), b(b) {}

	int getB() {
		return b;
	}

	void print() {
		A::print();
		cout << "b=" << b << endl;
	}

};


int main() {

	cout << endl << "A" << endl;

	A aObj(2);
	aObj.print();
	foo(&aObj);

	cout << "sizeOf(A)=" << sizeof(A) << endl;
	cout << "&aObj=" << &aObj << endl;
	cout << "&aObj.a=" << &aObj.a << endl;

	cout << endl << "B" << endl;

	B bObj(3, 4);
	bObj.print();
	int aInBObj = bObj.getA();
	foo(&bObj);

	cout << "sizeOf(B)=" << sizeof(B) << endl;
	cout << "&bObj=" << &bObj << endl;
	cout << "&bObj.a=" << &bObj.a << endl;
	cout << "&bObj.b=" << &bObj.b << endl;
	A* pa = &bObj;
	cout << "(A*)&bObj=" << pa << endl;


	return 0;
}