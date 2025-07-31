#include <iostream>
#include <string>
#include <cstdint>
using namespace std;

#define size_type string::size_type

class stack {
public:
	string str;
	size_type size = 0;
	bool input(string data) {
		size += data.size();
		str += data;
		return true;
	}
	bool input(char data) {
		size++;
		str += data;
		return true;
	}
	char output(size_type size) {
		//cout << "his->size" << this->size << endl << "size" << size << endl;
		if (this->size < size)
			return '0';
		if (size == 0)
			return str[0];
		return str[size- 1];
	}
	char output() {
		if (size == 0)
			return str[size];
		return str[size- 1];
	}
	bool remove(size_type size) {
		if (this->size < size)
			return false;
		//this->size - size
		str.erase(size, this->size - size);
		this->size -= this->size - size;
		return true;
	}
	bool remove() {
		if (this->size < size)
			return false;
		str.erase(size - 1, 1);
		size--;
		return true;
	}
	bool bracket_checking(string str) {
		stack L;
		for (char c : str) {
			if (c == '(' || c == '[' || c == '{')
				L.input(c);
			if (c == ')' || c == ']' || c == '}') {
				if (L.size == 0)
					return false;
				if (L.output() == c)
					return false;
				cout << L.size << endl;
				if ((L.output() == '(' && c != ')') ||
					(L.output() == '[' && c != ']') ||
					(L.output() == '{' && c != '}'))
					return false;
				L.remove();
			}
		}
		if (L.size == 0)
			return true;
		cout << "  " << endl;
		return false;
	}
};





int32_t main() {
	stack L;
	size_type size = 0;
	//for (char i = 97; i < 107; i++) {
	//	L.input(i);
	//	size++;
	//	cout << L.output(size) << endl;
	//}
	L.input("(()){}[]()");
	//L.remove();
	for (int32_t i = 0; i < L.size; i++)
		cout << L.output(i) << endl;
	cout << L.bracket_checking("(()){}[]()");
	return 0;
}