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

	void setA(int a) {
		this->a = a;
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

	cout << "In foo(" << ptr << "): " << endl;

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

class C : public A {

public: // для демонстрации адреса поля
	int c;

public:

	C(int a, int c) : A(a), c(c) {}

	int getC() {
		return c;
	}

	virtual void write() {
		C::print();
	}

	void print() {
		A::print();
		cout << "c=" << c << endl;
	}

};

class D : public B, public C {

public: // для демонстрации адреса поля
	int d;

public:

	D(int a, int b, int c, int d) : B(a, b), C(a, c), d(d) {}

	void print() {
		B::print();
		C::write();
		cout << "d=" << d << endl;
	}

	void write() {
		D::print();
	}
};

void modifyB(B* ptr, int newA) {
	ptr->setA(newA);
}

void showB(B* ptr) {
	ptr->A::print();
}

void showC(C* ptr) {
	ptr->A::print();
}

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
	cout << "(A*)&bObj=" << pa << "; &bObj" << &bObj << endl;

	// В случае, если класс A содержит виртуальные методы, то А - полиморфный класс
	// Структура объекта класса B:
	// B : { A : { vprt, a} , b }
	// В этом случае (A*) &bObj == (B*) &bObj

	// В случае, если в классе A нет виртуальных методов (А - неполиморфный класс), 
	// а в классе B - есть виртуальные методы, то структура объекта класса B:
	// B : { vptr, A: { a }, b }
	// В этом случае (A*) &bObj != (B*) &bObj

	cout << endl << endl << "D" << endl;

	cout << "sizeOf(D)=" << sizeof(D) << endl;
	D dObj(1, 2, 3, 4);
	cout << "&dObj=" << &dObj << endl;
	cout << "&dObj.B::a=" << &dObj.B::a << endl;
	cout << "&dObj.b=" << &dObj.b << endl;
	cout << "&dObj.C::a=" << &dObj.C::a << endl;
	cout << "&dObj.c=" << &dObj.c << endl;
	cout << "&dObj.d=" << &dObj.d << endl;
	// D : { B : { A : { vprt, a} , b },  C : { A : { vprt, a}, c }, d }

	modifyB(&dObj, 6);
	dObj.print();

	showB(&dObj);
	showC(&dObj);

	return 0;
}