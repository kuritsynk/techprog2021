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

	void print() {
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

class B : public A {

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

	virtual void print() {
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
	cout << "(A*)&bObj=" << pa << "; &bObj" << &bObj << endl;

	// � ������, ���� ����� A �������� ����������� ������, �� � - ����������� �����
	// ��������� ������� ������ B:
	// B : { A : { vprt, a} , b }
	// � ���� ������ (A*) &bObj == (B*) &bObj

	// � ������, ���� � ������ A ��� ����������� ������� (� - ������������� �����), 
	// � � ������ B - ���� ����������� ������, �� ��������� ������� ������ B:
	// B : { vptr, A: { a }, b }
	// � ���� ������ (A*) &bObj != (B*) &bObj

	return 0;
}