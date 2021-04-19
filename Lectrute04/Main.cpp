#include <iostream>

using namespace std;



class A {

public: // ��� ������������ ������ ����
	// vptr -- ��������� �� ������� ����������� ������� vtable_A, ������� �������� ������ 
    // vtable_A: 0: "print"-> A_print_A*
	// ���� ����������� ������� � ������

	int a;

public:
	A(int a) : 
		// vptr(&vtable_A), 
		a(a) {
	
		cout << "In class A constructor: " << this << endl;
		print(); // ������ ����� ���������� A_print_A*(this)
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
	// ������ ����������:
	// if (A_getA_A*(ptr) > 0) {
	//    A_print_A*(ptr);
	// }


	// ������� ���������� ��� print():
	// if (A_getA_A*(ptr) > 0) {
	//    ptr->vptr["print"](ptr);  
	// ���������� ����������� ����� ������� �� ������, ����������� ����� ��������� vptr
	// �� ��������� ��� ������ "print" 
	// }

	cout << "In foo(" << ptr << "): " << endl;

	if (ptr->getA() > 0) {
		ptr->print();
	}
}

class B : virtual public A {

public: // ��� ������������ ������ ����

	int b;

public:

	B(int a, int b) : A(a), 
		// vptr(&vtable_B),   // ������������� ��������� �� VMT ���������� ����� ������ ������������ �������� ������
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

class C : virtual public A {

public: // ��� ������������ ������ ����
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

public: // ��� ������������ ������ ����
	int d;

public:

	D(int a, int b, int c, int d) : A(a), B(a, b), C(a, c), d(d) {}

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

// ����������� ����� (������ ������� ��� ���������)
class Printable {
public:
	// ������ ����������� �������
	virtual int getValue() = 0;

	// ������ ����������� �������
	virtual void print() = 0;
};

class F : public Printable {
	int f;

public:
	F(int f) : f(f) {}

	int getValue() {
		return f;
	}

	void print() {
		cout << "f=" << f << endl;
	}
};

void fooPrint(Printable* ptr) {
	if (ptr->getValue() > 0) {
		ptr->print();
	}
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

	// � ������, ���� ����� A �������� ����������� ������, �� � - ����������� �����
	// ��������� ������� ������ B:
	// B : { A : { vprt, a} , b }
	// � ���� ������ (A*) &bObj == (B*) &bObj

	// � ������, ���� � ������ A ��� ����������� ������� (� - ������������� �����), 
	// � � ������ B - ���� ����������� ������, �� ��������� ������� ������ B:
	// B : { vptr, A: { a }, b }
	// � ���� ������ (A*) &bObj != (B*) &bObj

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

	cout << endl << endl << "Abstract classes" << endl;

	// Printable pr; // ������ �������� ��������� ������������ ������

	// F f(2); // f - �����������, �� ��� ���, ���� �� ���������� ��� ������ ����������� �������

	F f(2);
	fooPrint(&f);

	return 0;
}