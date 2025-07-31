#include <iostream>
#include <cstdint>
using namespace std;

#define MAX_QUEUE_SIZE 10


class queue {
public:
	int32_t data[MAX_QUEUE_SIZE] = { 0 };
	int32_t size = 0;
	int32_t raer = 0;
	int32_t front = 0;
	bool input(int32_t data) {
		if (full_sentence())//ÂúÁË
			return false;
		size++;
		this->data[raer] = data;
		if (raer == MAX_QUEUE_SIZE - 1) { //raer == 9
			change_0(raer);
			return true;
		}
		raer++;
		return true;
	}
	bool remove() {
		if (empty())//¿ÕÁË
			return false;
		size--;
		this->data[front] = 0;
		if (front == MAX_QUEUE_SIZE - 1) { //front == 9
			change_0(front);
			return true;
		}
		front++;
		return true;
	}
	bool change_0(int32_t &data) {
		data = 0;
		return true;
	}
	int32_t check(uint32_t location) {
		if (location > size)
			return false;
		if (location == 0)
			return false;
		if (location > MAX_QUEUE_SIZE)// ? > 10
			return false;
		if (location + front - 1 > MAX_QUEUE_SIZE)
			return data[location + front - 1 - MAX_QUEUE_SIZE];
		return data[location + front - 1];
	}
	bool empty() {
		if (size == 0)
			return true;
		return false;
	}
	bool full_sentence() {
		if (size == MAX_QUEUE_SIZE)
			return true;
		return false;
	}
};

int32_t main() {
	queue Q;
	Q.input(10);
	cout << Q.check(1) << endl;
	cout << Q.empty() << endl << Q.full_sentence() << endl;
	for (int32_t i = 0; i < MAX_QUEUE_SIZE; i++) {
		cout << "Q.input(i):" << Q.input(i) << endl;
		cout << "i:" << i << endl;
		cout << Q.check(i + 1) << endl;
		cout << "size:" << Q.size << endl;
	}
	return 0;
}