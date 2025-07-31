#include <iostream>
#include <cstdint>
#include <stack>
#include <string>
#include <limits>
using namespace std;
namespace data_priority {
	int8_t add = '+';
	int8_t subtract = '-';
	int8_t take = '*';
	int8_t d_m = '/';	// division_method
	int8_t q_b = '(';	//qpen_bracket
	int8_t c_b = ')';	//close_bracket
	const int16_t arr_size = 6;
	int16_t arr_priority[arr_size] = { add, subtract, take, d_m, q_b, c_b };
	int16_t operator1 = 1;
	int16_t operator2 = 2;
	int16_t operator3 = 3;
	int16_t data_priority = 0;
}

bool judgment_operator(char data);
int16_t judgment_operator_data(char data);
char operator_data(char data);

int32_t computation(int32_t after, int32_t before, int32_t arr_data) {
	int32_t new_data = 0;
	if (arr_data == 0)
		new_data = before + after;
	if (arr_data == 1)
		new_data = before - after;
	if (arr_data == 2)
		new_data = before * after;
	if (arr_data == 3)
		new_data = before / after;
	return new_data;
}
int32_t computation_data(string str) {
	stack<int32_t> data;
	stack<int8_t> operator_data;
	int32_t punctuation = 0;
	//cout << 1 << endl;
	for (int32_t i = 0; i < str.size(); i++) {
		//cout << 2 << endl;
		if (str[i] == ' ') {
			//cout << 3 << endl;
			int32_t p = punctuation;
			string data_temp;
			while (p <= i) {
				//cout << 4 << endl;
				data_temp += str[p];
				p++;
			}
			//cout << 6 << endl;
			//cout << data_temp << endl;
			punctuation = i + 1;
			data.push(stoi(data_temp));
		}
		if (str[i] == ' ') {
			int16_t operator_punctuation = i + 1;
			for (int32_t j = 0; j < data_priority::arr_size; j++)
				if (str[operator_punctuation] == data_priority::arr_priority[j]) {
					operator_data.push(str[operator_punctuation]);
					int32_t new_data = 0;
					int32_t after = data.top();
					data.pop();
					int32_t before = data.top();
					data.pop();
					new_data = computation(after, before, j);
					data.push(new_data);
					i += 2;
					punctuation = i + 1;
					//cout << operator_data.top() << endl;
					continue;
				}
		}
	}
	//cout << 5 << endl;
	if (data.size() != 1)
		return false;
	cout << data.size() << endl;
	for (int32_t i = 0; i < data.size(); i++) 
		cout << "data:" << data.top() << endl;
	return operator_data.top();
}
int32_t conversion(string str) {
	for (int32_t i = 0; i <= str.size(); i++) {
		int8_t remove_data = ' ';
		if (str[i] == remove_data) 
			//cout << 1 << endl;
			str.erase(str.begin() + i);
		cout << str << endl;
	}
	for (int32_t i = 0; i <= str.size(); i++) {
		if (str[i] == ::operator_data(str[i]) && str[i] != '0') {
			str.insert(i , " ");
			i += 1;
			str.insert(i + 1, " ");
			i += 1;
		}
		cout << str << endl;
	}
	string str_data;
	stack<int32_t> data;
	stack<int8_t> operator_data;
	int32_t punctuation = 0;
	bool spaces = true;
	for (int32_t i = 0; i <= str.size(); i++) {
		cout << str_data << endl;
		if (str[i] == ' ' && spaces == true) {
			cout << str_data << endl;
			cout << punctuation << endl;
			cout << i << endl;
			str_data += str.substr(punctuation, i) + " ";
			punctuation = i + 3;
			spaces = false;
		}
		else
			spaces = true;
		if (str[i] == ::operator_data(str[i]) && str[i] != '0') {
			int32_t operator_punctuation = judgment_operator_data(str[i]);
			//cout << operator_punctuation << endl;
			//cout << operator_data.size() << endl;
			/*
			遇到运算符。依次弹出栈中优先级高于或等于当前运算符的所有运算符，
			并加入后缀表达式，若碰到“(”或栈空则停止。之后再把当前运算符入栈。
			*/
			if (operator_data.size() == 0) {
				operator_data.push(str[i]);
				//cout << "==" << operator_data.top() << endl;
			}
			//cout << operator_data.top() << endl;
			else if (operator_punctuation <= judgment_operator_data(operator_data.top())) {
				//cout << operator_data.top() << endl;
				operator_data.pop();
			}
			else if (operator_punctuation > judgment_operator_data(operator_data.top())) {
				operator_data.push(str[i]);
				//cout << ">" << operator_data.top() << endl;
			}
			//cout << operator_data.top() << endl;
		}
	}
	cout << operator_data.size() << endl;
	cout << str_data << endl;
	cout << str.substr(0, 5 - 1) << endl;;
	for (int32_t i = 0; i < operator_data.size(); i++) {
		cout << operator_data.top();
		operator_data.pop();
	}
	return 0;
}
int16_t judgment_operator_data(char data) {
	if (data == '+')
		return 1;
	if (data == '-')
		return 1;
	if (data == '*')
		return 2;
	if (data == '/')
		return 2;
	if (data == '(')
		return 3;
	if (data == ')')
		return 3;
	return false;
}
bool judgment_operator(char data) {
	if (data == '+')
		return true;
	if (data == '-')
		return true;
	if (data == '*')
		return true;
	if (data == '/')
		return true;
	return false;
}
char operator_data(char data) {
	if (data == '+')
		return '+';
	if (data == '-')
		return '-';
	if (data == '*')
		return '*';
	if (data == '/')
		return '/';
	return '0';
}
int32_t main() {
	string str1 = "1110 110 - 110 + 1111 *";
	string str2 = "1110 + 110 / 110 / 1111";
	//computation_data(str1);
	conversion(str2);
	return 0;
}