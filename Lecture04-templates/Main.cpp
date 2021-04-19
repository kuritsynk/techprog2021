#include <iostream>

using namespace std;

// перегрузка функкций
//int min(int a, int b) {
//	return a < b ? a : b;
//}
//
//float min(float a, float b) {
//	return a < b ? a : b;
//}

// шаблонная функция
template <typename T>
T min(T a, T b) {
	return a < b ? a : b;
}

int min(int a, int b) {
	return a < b ? a : b;
}


template<typename T>
class Vector {

	T* data;
	int size;

public:

	// методы класса

	// Vector_getSize(Vector*_int)
	void setSize(int size);

	// Vector_setSize(const Vector*)
	int getSize() const {
		return size;
	}
	T* getData() const {
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

	T& operator[](int index) {
		if (index < 0 || index >= size) {
			throw "Некорректный индекс";
		}
		return data[index];
	}

};

template <typename T>
void Vector<T>::setSize(int size) {
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

	data = new T[size];
	this->size = size;
}


int main() {
	int k = min<int>(1, 2);
	int l = min(3, 4);

	cout << "min(3.14, 2.7)=" << min(3.14, 2.7) << endl;


	Vector<int> v1(5);
	Vector<int> v2(5);
	v2 = v1;
	v2[1] = 5;

	Vector<double> v3(5);
	// v3 = v1;
	v3[2] = 3.14;


	return 0;
}