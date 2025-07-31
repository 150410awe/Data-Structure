#include <iostream>
#include <cstdint>

using namespace std;

#define STACK_ARR_MAX_SIZE 10
class stack {
public:
	bool input(int32_t data) {
		if (location > STACK_ARR_MAX_SIZE - 1)
			return false;
		input_prototype(data);
		return true;
	}
	int32_t output(int32_t location) {
		if (location > this->location)
			return false;
		return arr[location - 1];
	}
	bool remove() {
		if (location < 0)
			return false;
		remove_prototype();
		return true;
	}
	int32_t location = 0;
private:
	void input_prototype(int32_t data) {
		arr[location] = data;
		location++;
	}
	void remove_prototype() {
		arr[location - 1] = 0;
		location--;
	}
	int32_t arr[STACK_ARR_MAX_SIZE] = { 0 };

};

int32_t main() {
	stack S;
	for (int32_t i = 0; i < STACK_ARR_MAX_SIZE; i++) {
		S.input(i);
		cout << S.output(i + 1) << endl;
	}
	cout << endl;
	cout << S.location << endl;
	S.remove();
	for (int32_t i = 0; i < STACK_ARR_MAX_SIZE; i++) {
		cout << S.output(i + 1) << endl;
	}
	cout << S.location << endl;
	return 0;
}