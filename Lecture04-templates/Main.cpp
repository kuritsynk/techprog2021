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


template<typename T, int size>
class Vector {

	T data[size];

public:

	int getSize() const {
		return size;
	}

	T& operator[](int index) {
		if (index < 0 || index >= size) {
			throw "Некорректный индекс";
		}
		return data[index];
	}

};

int main() {
	int k = min<int>(1, 2);
	int l = min(3, 4);

	cout << "min(3.14, 2.7)=" << min(3.14, 2.7) << endl;


	Vector<int, 5> v1;
	v1[2] = 3;

	Vector<int, 5> v2;
	v2 = v1;
	v2[1] = 5;
	cout << "v2[2]=" << v2[2] << endl;

	Vector<int, 10> v4;

	//v4 = v1;

	Vector<double, 5> v3;
	v3[2] = 3.14;


	return 0;
}