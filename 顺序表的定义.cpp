#include <iostream>
#include <cstdint>

using namespace std;
#define arr_size 10

class class_arr {
public:
	int32_t *arr = NULL;
	int32_t class_arr_size = arr_size;
	int32_t class_arr_capacity = arr_size;
};

void arr_O(class_arr &arr);
void change_arr_size(class_arr arr, const int32_t new_capacity);

int main() {
	class_arr arr;
	arr_O(arr);
	delete arr.arr;

	return 0;
}


void arr_O(class_arr &arr) {
	arr.arr = new int32_t[arr_size];
	for (int i = 0; i < arr_size; i++){
		arr.arr[i] = i;
		cout << "arr[" << i << "] = " << arr.arr[i] << endl;
	}
}


void change_arr_size(class_arr arr, const int32_t new_capacity) {
	int32_t* new_q = new int32_t[new_capacity];

	for (int i = 0; i < arr.class_arr_size; i++) {
		new_q[i] = arr.arr[i];
	}
	arr.arr = new_q;
	delete new_q;
}