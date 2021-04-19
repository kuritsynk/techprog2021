#include <iostream>

using namespace std;

class A {

public: // для демонстрации адреса поля
	// vptr -- указатель на таблицу виртуальных функций vtable_A, которая содержит адреса 
    // vtable_A: 0: "print"-> A_print_A*
	// всех виртуальных функций в классе

	int a;

public:
	A(int a) : 
		// vptr(&vtable_A), 
		a(a) {
	
		cout << "In class A constructor: " << this << endl;
		print(); // всегда будет вызываться A_print_A*(this)
	}

	int getA() {
		return a;
	}

	virtual void print() {
		cout << "a=" << a << endl;
	}

};


void foo(A* ptr) {
	// Раннее связывание:
	// if (A_getA_A*(ptr) > 0) {
	//    A_print_A*(ptr);
	// }


	// Позднее связывание для print():
	// if (A_getA_A*(ptr) > 0) {
	//    ptr->vptr["print"](ptr);  
	// компилятор подставляет вызов функции по адресу, полученному через указатель vptr
	// со смещением для метода "print" 
	// }


	if (ptr->getA() > 0) {
		ptr->print();
	}
}

class B : public A {

public: // для демонстрации адреса поля

	int b;

public:

	B(int a, int b) : A(a), 
		// vptr(&vtable_B),   // инициализация указателя на VMT происходит после вызова конструктора базового класса
		// vtable_B: 0: "print"-> B_print_B*
		b(b) {}

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