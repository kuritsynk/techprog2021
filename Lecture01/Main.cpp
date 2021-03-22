#include <iostream>

// max_int_int
int max(int a, int b) {
	return 0;
}

// max_float_float
float max(float a, float b) {
	return 0;
}

namespace MySpase {
	// MySpase_max_int_int
	int max(int a, int b) {
		return 0;
	}
}


// vector ����������� size � �������������� ������������
int* data1;
int size1;

int* data2;
int size2;

int mult(int* data1, int size1,
	int* data2, int size2) {
	// ������ ��������� ������������ ������� ���������� (��� ��������� �������)
	if (size1 != size2) {
		throw "������� �������� ������ ���������";
	}



	// ����������� ��������� ������������ ���� ��������
	return true;
}

class Vector {

	// ���� ������

	// private: // ������ ���� ������ � ������ ������ � ������ ������
	int* data;
	int size;

public:

	// ������ ������

	// Vector_getSize(Vector*_int)
	void setSize(int size);

	// Vector_setSize(Vector*)
	int getSize() {
		return size;
	}
	int* getData() {
		return data;
	}

private:

public:

	Vector() : size(0), data(nullptr) {
		// ����������� �� ���������
	}

	Vector(int size) : data(nullptr), size(0) {
		setSize(size);
	}

	~Vector() {
		setSize(0);
	}

};

// void Vector_setSize_Vector*_int(Vector* this, int size) {
// 	this->data = new int[size];
//  this->size = size;
// }
void Vector::setSize(int size) {
	if (size < 0) {
		throw "������ ������ ���� ���������������";
	}
	
	if (this->size == size) {
		return;
	}

	if (data != nullptr) {
		delete[] data;
		data = nullptr;
		this->size = 0;
	}

	if (size == 0) {
		return;
	}

	data = new int[size];
	this->size = size;
}

int multiplyVectors(Vector v1, Vector v2) {
	return 0;
}

int main() {

	std::cout << "Hello world" << std::endl;

	// ������������� ���� �������.
	// ������ ����������
	int k = max(2, 3); // max_int_int
	k = MySpase::max(2, 3); // MySpace_int_int

	// 0 ���

	int size1 = 6;
	int* data1 = new int[size1];

	int size2 = 5;
	int* data2 = new int[size2];

	int size3 = 6;

	int m = mult(data1, size1, data2, size3);

	// 2 ��� - ���������� ������

	Vector v1; // ���������� ����������� �� ���������
	Vector v2;

	std::cout << "sizeof(v1)" << sizeof(v1);

	//v1.data = new int[5];
	//v1.size = 6;

	//m = mult(v1.data, v1.size, v2.data, v2.size);


	// 3 ��� - ������

	v1.setSize(5); // Vector_setSize_Vector*_int(&v1, 5);
	v2.setSize(5); // Vector_setSize_Vector*_int(&v2, 5);
	// m = mult(v1.getData(), v1.getSize(), v2.getData(), v2.getSize());
	m = multiplyVectors(v1, v2);

	v1.setSize(5);
	v1.setSize(15);
	v1.setSize(5);
	v1.setSize(35);

	v1.setSize(0);

	// 4 ��� - ������������ � �����������

	Vector v3(5); // Vector(5); Vector_Vector*_int(&v3, 5);
	Vector v4(5);
	int m2 = multiplyVectors(v3, v4);

	{
		Vector v5;

	} // v5.~Vector(); // Vector_~Vector_Vector*(&v5)

	// 4.1 ��� - new � delete ��� ��������

	// �������� new 1) �������� sizeof(Vector) ����
	// 2) �������� ����������� �������
	// 3) ���������� ��������� �� ��������� ������
	Vector* vptr = new Vector(5);
	// vptr = new Vector;

	std::cout << "vptr->size=" << vptr->getSize() << std::endl; // 5

	// �������� delete 1) �������� ���������� ������� Vector_~Vector_Vector*(vptr)
	// 2) ����������� ������ �� ���������
	delete vptr;

	// ����� ���������� 10 ��� ����������� Vector �� ���������
	Vector* varray = new Vector[10]; 
	for (int i = 0; i < 10; ++i) {
		varray->setSize(5);
	}

	delete[] varray;


	return 0;
} // v4.~Vector(), v3.~Vector()....