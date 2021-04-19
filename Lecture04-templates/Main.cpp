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



int main() {
	int k = min<int>(1, 2);
	int l = min(3, 4);

	cout << "min(3.14, 2.7)=" << min(3.14, 2.7) << endl;

	return 0;
}