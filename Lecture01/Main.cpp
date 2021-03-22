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


// vector размерности size с целочисленными координатами
int* data1;
int size1;

int* data2;
int size2;

int mult(int* data1, int size1,
	int* data2, int size2) {
	// всегда проверяем корректность входных параметров (для публичных функций)
	if (size1 != size2) {
		throw "Размеры векторов должны совпадать";
	}



	// выполняется скалярное произведение двух векторов
	return true;
}

class Vector {

	// поля класса

	// private: // доступ есть только у членов класса и друзей класса
	int* data;
	int size;

public:

	// методы класса

	// Vector_getSize(Vector*_int)
	void setSize(int size);

	// Vector_setSize(const Vector*)
	int getSize() const {
		return size;
	}
	int* getData() const {
		return data;
	}

private:

public:

	Vector() : size(0), data(nullptr) {
		// конструктор по умолчанию
	}

	Vector(int size) : data(nullptr), size(0) {
		setSize(size);
	}

	Vector(const Vector& src) : data(nullptr), size(0) {
		setSize(src.size);
		for (int i = 0; i < size; ++i) {
			data[i] = src.data[i];
		}
	}

	~Vector() {
		setSize(0);
		//std::cout << "Destroying ..." << this << std::endl;
	}

	Vector& operator=(const Vector& r) {

		if (this == &r) {
			return *this;
		}

		setSize(r.size);
		for (int i = 0; i < size; ++i) {
			data[i] = r.data[i];
		}

		return *this;
	}

};

// void Vector_setSize_Vector*_int(Vector* this, int size) {
// 	this->data = new int[size];
//  this->size = size;
// }
void Vector::setSize(int size) {
	if (size < 0) {
		throw "Размер должен быть неотрицательным";
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

// Передача параметра по значению
// v - побитовая копия передаваемого значения (v7 в примере на шаге 5)
// Vector v(v7): v.size = v7.size, v.data = v7.data
void printVector(Vector v) {
	for (int i = 0; i < v.getSize(); ++i) {
		std::cout << v.getData()[i] << std::endl;
	}
} // v.~Vector() -> будет освобождена память по указателю v.data (v7.data)

int multiplyVectors(Vector v1, Vector v2) {
	return 0;
}

int main() {

	std::cout << "Hello world" << std::endl;

	// Декорирование имен функций.
	// Раннее связывание
	int k = max(2, 3); // max_int_int
	k = MySpase::max(2, 3); // MySpace_int_int

	// 0 шаг

	int size1 = 6;
	int* data1 = new int[size1];

	int size2 = 5;
	int* data2 = new int[size2];

	int size3 = 6;

	int m = mult(data1, size1, data2, size3);

	// 2 шаг - объявление класса

	Vector v1; // вызывается конструктор по умолчанию
	Vector v2;

	std::cout << "sizeof(v1)" << sizeof(v1);

	//v1.data = new int[5];
	//v1.size = 6;

	//m = mult(v1.data, v1.size, v2.data, v2.size);


	// 3 шаг - методы

	v1.setSize(5); // Vector_setSize_Vector*_int(&v1, 5);
	v2.setSize(5); // Vector_setSize_Vector*_int(&v2, 5);
	// m = mult(v1.getData(), v1.getSize(), v2.getData(), v2.getSize());
	m = multiplyVectors(v1, v2);

	v1.setSize(5);
	v1.setSize(15);
	v1.setSize(5);
	v1.setSize(35);

	v1.setSize(0);

	// 4 шаг - конструкторы и деструкторы

	Vector v3(5); // Vector(5); Vector_Vector*_int(&v3, 5);
	Vector v4(5);
	int m2 = multiplyVectors(v3, v4);

	{
		Vector v5;

	} // v5.~Vector(); // Vector_~Vector_Vector*(&v5)

	// 4.1 шаг - new и delete для объектов

	// Оператор new 1) выделяет sizeof(Vector) байт
	// 2) вызывает конструктор объекта
	// 3) возвращает указатель на созданный объект
	Vector* vptr = new Vector(5);
	// vptr = new Vector;

	std::cout << "vptr->size=" << vptr->getSize() << std::endl; // 5

	// Оператор delete 1) вызывает деструктор объекта Vector_~Vector_Vector*(vptr)
	// 2) освобождает память по указателю
	delete vptr;

	// Здесь вызывается 10 раз конструктор Vector по умолчанию
	Vector* varray = new Vector[10]; 
	for (int i = 0; i < 10; ++i) {
		varray->setSize(5);
	}

	delete[] varray;

	// 5 шаг - Передача объектов в функции
	
	std::cout << "=== 5 ===" << std::endl;


	Vector v7(5);
	for (int i = 0; i < v7.getSize(); ++i) {
		v7.getData()[i] = i;
	}


	printVector(v7);
	printVector(v7);


	// Шаг 6

	Vector v8(5);  
	Vector v9(v8); // конструктор копирования
	
	Vector v10 = v8; // конструктор копирования Vector_Vector_Vector*_Vector&(&v10, v8)
	// создается новый объект-копия

	v9 = v10 = v8; // оператор присваивания // v10.operator=(v8) // Vector_operator=_Vector*_Vector&(&v10, v8)
	// новый объект не создается, а заполняется существующий

	v10 = v10; // отдельный случай, который надо проверять

	Vector* vptr10 = &v10;
	v10 = *vptr10; // присвоение самому себе


	return 0;
} // v4.~Vector(), v3.~Vector()....