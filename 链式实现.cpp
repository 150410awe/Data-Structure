#include <iostream>
#include <cstdint>

using namespace std;

#define NULLPTR nullptr

class queue_node
{
public:
	int32_t data = 0;
	queue_node* next = NULLPTR;
};


class queue {
public:
	queue* head = this;
	queue_node* tail = NULLPTR;
	int32_t data = 0;
	int32_t size = 0;
	queue_node* next = NULLPTR;

	bool increase(int32_t data) {
		queue_node* new_node = new queue_node;
		next = new_node;
		new_node->data = data;
		size++;
		tail = new_node;
		cout << size << " " << new_node << endl;
		return true;
	}
	bool remove() {
		if (check_empty()) {
			return false;
		}
		queue_node* temp = this->next->next;
		delete this->next;
		this->next = temp;
		size--;
		return true;
	}
	queue_node* lookup(int32_t data) {
		cout << data << endl;
		for (queue_node* p = head->next; p != NULLPTR; p = p->next) {
			cout << p << endl;
			if (p->data == data)
			return p;
		}
		return NULLPTR;
	}
	bool check_empty() {
		if (size < 1)
			return true;
		return false;
	}
};



int32_t main() {
	queue L;
	L.increase(10);
	cout << L.size << endl << L.next->data << endl;
	cout << L.check_empty() << endl;
	cout << L.lookup(10) << " " << L.next << endl;;
	for (int i = 0; i < 10; i++) {
		cout << i << endl;
		L.increase(i);
		cout << L.lookup(i)->data << endl;;
	}
	cout << L.lookup(0)->data << endl;
	for (int i = 0; i < 10; i++)
		//cout << L.lookup(i)->data << endl;
	return 0;
}