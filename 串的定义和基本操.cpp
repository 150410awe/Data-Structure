#include <iostream>
#include <string>
#include <cstdint>

using namespace std;

#define NULLPTR nullptr
#define ARRMAX 255

class mystring {
public:
	int32_t size = 0;
	int8_t arr[ARRMAX] = "";
	bool add(int8_t const input_arr[], int32_t input_arr_size) {
		cout << "Input size: " << input_arr_size << endl;
		if (input_arr_size + size >= ARRMAX)
			return false;
		for (int32_t i = 0; i < input_arr_size; i++)
			arr[i + size] = input_arr[i];
		size += input_arr_size;
		arr[size] = '\0';
		cout << "New size: " << size << endl;
		return true;
	}
	bool add(int8_t (&new_string)[ARRMAX], int32_t new_string_size, int8_t const arr1[], int8_t const arr2[],int32_t arr1_size, int32_t arr2_size) {
		if (arr1_size + arr2_size + new_string_size >= ARRMAX)
			return false;
		for (int32_t i = 0; i < arr1_size; i++)
			new_string[i + new_string_size] = arr1[i];
		for (int32_t i = 0; i < arr2_size; i++)
			new_string[i + new_string_size + arr2_size] = arr2[i];
		new_string[new_string_size + arr1_size + arr2_size] = '\0';
		return true;
	}
	bool assignment(int8_t const new_fu[], int32_t new_fu_size) {
		if (new_fu_size >= ARRMAX)
			return false;
		size = new_fu_size;
		for (int32_t i = 0; i < new_fu_size; i++)
			arr[i] = new_fu[i];
		arr[size] = '\0';
		return true;
	}
	bool replication(int8_t const string[], int32_t string_size, int8_t (&replication_string)[ARRMAX]) {
		if (string_size >= ARRMAX)
			return false;
		for (int32_t i = 0; i < string_size; i++) 
			replication_string[i] = string[i];
		replication_string[string_size] = '\0';
		return true;
	}
	bool empty(int8_t const string[]) {
		if (string == NULLPTR)// !string
			return false;
		if (string[0] == '\0')
			return true;
		return false;
	}
	int32_t string_size(int8_t const string[]) {
		if(string == NULLPTR)
			return false;
		for (int32_t i = 0; i < ARRMAX; i++)
			if (string[i] == '\0')
				return i;
		return false;
	}
	bool clear_out(int8_t string[]) {
		if (string == NULLPTR)
			return false;
			string[0] = '\0';
		return true;
	}
	bool clear_out() {
		if (arr == NULLPTR)
			return false;
		arr[0] = '\0';
		size = 0;
		return true;
	}
	bool destruction(int8_t* p) {
		if (p == NULLPTR)
			return false;
		delete[] p;
		return true;
	}
	int32_t finding_substring(int8_t substring[], const string string,int32_t substring_size) {
		int32_t finding_num = substring_size - int32_t(string.size()) + 1;
		if (finding_num <= 0 || string.empty() || substring == NULLPTR)
			return -1;
		for (int32_t i = 0; i < finding_num; i++) {
			bool match = true;
			for (int32_t j = 0; j < string.size(); j++) 
				if (substring[j + i] != string[j]) {
					match = false;
					break;
				}
			if (match == true)
				return i;
		}
		return -1;
	}
	int32_t finding_substring_kmp(int8_t substring[], const string string, int32_t substring_size) {
		if (substring == NULLPTR || substring_size <= 0 || string.empty() || string.size() > substring_size)
			return -1;
		int32_t* next = new int32_t[string.size()]{ -1 };
		next[1] = 0;
		for (int32_t i = 1; i < string.size(); i++) {
			int32_t refixes = 0;
			int32_t suffix = i;
			int32_t MAX = 0;
			for (int32_t j = 1; j < i; j++) 
				if (string.substr(refixes, j - 1) == string.substr(suffix--, i)) 
					if (MAX < j + 1)
						MAX = j;
			if (next[i] == -1)
				next[i] = 1;
			else 
				next[i] = MAX;
		}
		int32_t j = 0;
		for (int32_t i = 0,j = 0; i < substring_size;) {
			if (substring[i] == string[j]) {
				i++;
				j++;
				if (j == string.size()) {
					delete[] next;
					return i - j;
				}
			}
			else 
				j = next[j];
			if (j == -1) {
				i++;
				j = 0;
			}
		}
		delete[] next;
		return -1;
	}
};


int32_t main() {
	int8_t a[10] = "100000000";
	//cout << "Array size: " << sizeof(a) << endl;
	mystring b;
	//b.add(a, sizeof(a) - 1);
	//cout << "Content: " << b.arr << endl;
	//cout << "Length: " << b.size << endl;
	int8_t c[10] = "123456789";
	//b.assignment(c, sizeof(c) - 1);
	//cout << b.arr << endl << b.size << endl;
	int8_t d[ARRMAX] = "1313413";
	//b.replication(c, sizeof(c), d);
	//cout << d << endl;
	//int8_t* e = new int8_t[10];
	//e[1] = ' ';
	//b.destruction(e);
	//cout << e << endl;
	b.add(d, b.string_size(d), a, c, b.string_size(a), b.string_size(c)	);
	//cout << d << endl;
	b.assignment(d,b.string_size(d));
	//cout << b.arr << endl;
	//cout << b.finding_substring(b.arr, "123", b.size) << endl;
	return 0;
}