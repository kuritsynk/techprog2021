#include <iostream>

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


int main() {

	std::cout << "Hello world" << std::endl;

	return 0;
}