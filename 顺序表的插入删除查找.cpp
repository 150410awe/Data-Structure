#include <iostream>
#include <cstdint>

using namespace std;

void arr_O(int32_t* arr);
bool arr_insertion(int32_t* arr, int32_t location, int32_t insertion_num);
bool arr_delete(int32_t* arr, int32_t delete_num);
int32_t arr_repetition_lookup(int32_t* arr, int32_t lookup_num);
int32_t arr_subscript_lookup(int32_t* arr, int32_t lookup_subscript);
#define ARR_CAPACITY 100
#define ARR_SIZE 10
int32_t arr_size = ARR_SIZE;
int32_t arr_capacity = ARR_CAPACITY;
int32_t* arr = NULL;


int main() {
	arr = new int32_t[ARR_CAPACITY]{1,20,11,11,33,22,10,10,22};
	//arr_O(arr);
	cout << arr_insertion(arr, 3, 10) << endl;
	arr_delete(arr, 3);
	cout << arr_repetition_lookup(arr, 10) << endl;;
	cout << arr_subscript_lookup(arr, 1) << endl;
	return 0;
}



void arr_O(int32_t* arr) {
	for (int i = 0; i < ARR_SIZE; i++) {
		arr[i] = i;
		cout << "arr[" << i << "] = " << arr[i] << endl;
	}
}



bool arr_insertion(int32_t* arr, int32_t location, int32_t insertion_num) {
	if (location > arr_capacity)
		return false;
	if (location < 0)
		return false;
	if (arr_size == arr_capacity)
		return false;
	for (int32_t i = arr_size; i > location; i--) {
		arr[i] = arr[i - 1];
		cout << i << endl;
		cout << "arr[" << i << "] = " << arr[i] << endl;
	}
	arr[location] = insertion_num;
	cout << "arr[" << location << "] = " << arr[location] << endl;
	arr_size++;
	return true;
}



bool arr_delete(int32_t* arr, int32_t delete_num) {
	if (delete_num < 0)
		return false;
	if (delete_num > arr_size)
		return false;
	for (int32_t i = delete_num ; i < arr_size - 1; i++) {
		arr[i] = arr[i + 1];
		cout << i << endl;
		cout << "arr[" << i << "] = " << arr[i] << endl;
	}
	return true;
}


int32_t arr_repetition_lookup(int32_t* arr, int32_t lookup_num) {
	if (lookup_num < 0)
		return false;
	if (lookup_num > arr_size)
		return false;
	int32_t num = 0;
	for (int32_t i = 0; i < arr_size; i++)
		if (arr[i] == lookup_num)
			num++;
	return num;
}



int32_t arr_subscript_lookup(int32_t* arr, int32_t lookup_subscript) {
	if (lookup_subscript < 0)
		return false;
	if (lookup_subscript > arr_size)
		return false;
	return arr[lookup_subscript];
}