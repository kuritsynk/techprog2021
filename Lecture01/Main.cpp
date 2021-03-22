#include <iostream>

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


int main() {

	std::cout << "Hello world" << std::endl;

	return 0;
}