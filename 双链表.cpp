#include <iostream>
#include <cstdint>

using namespace std;

#define NULLPTR nullptr



class node {
public:
	int32_t data = 0;
	node* previous = NULLPTR;
	node* next = NULLPTR;
	//结点后插
	bool specifying_back_insert(int32_t data) {
		if (this->next == NULLPTR)
			return false;
		back_insert(data);
		return true;
	}
	//输入结点后插
	bool specifying_back_insert(node* input_node, int32_t data) {
		if (input_node->next == NULLPTR)
			return false;
		back_insert(input_node, data);
		return true;
	}
	//顺序后插
	bool order_back_insert(node& head, int32_t location, int32_t data) {
		if (head.next == NULLPTR)
			return false;
		node* p = traversal(head, location);
		if (p->next == NULLPTR)
			return tail_end_insertion(p, data);
		return specifying_back_insert(p, data);
	}
	//输入结点尾插
	bool tail_end_insertion(node* input_node, int32_t data) {
		if (input_node->next != NULLPTR)
			return false;
		node* new_node = new node;
		new_node->next = input_node->next;
		input_node->next = new_node;
		new_node->previous = input_node;
		new_node->data = data;
		return true;
	}
	//结点尾插
	bool tail_end_insertion(int32_t data) {
		if (this->next != NULLPTR)
			return false;
		node* new_node = new node;
		new_node->next = this->next;
		new_node->previous = this;
		this->next = new_node;
		new_node->data = data;
		return true;
	}
	//头尾插
	bool tail_end_insertion(node& head, int32_t data){
		if (head.next == NULLPTR)
			return true;
		node* p = traversal(head);
		back_insert(p, data);
		return true;
	}
	//打印
	bool print(node& head) {
		if (head.next == NULLPTR)
			return false;
		for (node* p = &head; p->next != NULLPTR; p = p->next)
			cout << p->data << endl;
		return true;
	}
	//初始化
	void initialization(node& head, int32_t node_num) {
		node* p = &head;
		for (int32_t i = 0; i <= node_num; i++) {
			node* node1 = new node;
			node1->previous = p;
			p->next = node1;
			p = node1;
		}
	}
private:
	//后插
	void back_insert(int32_t data) {
		node* new_node = new node;
		new_node->next = this->next;
		this->next->previous = new_node;
		this->next = new_node;
		new_node->previous = this;
		new_node->data = data;
	}
	//输入结点后插
	void back_insert(node* input_node,int32_t data) {
		node* new_node = new node;
		new_node->next = input_node->next;
		input_node->next->previous = new_node;
		input_node->next = new_node;
		new_node->previous = input_node;
		new_node->data = data;
	}
	//位置遍历
	node* traversal(node& head, int32_t location) {
		node* p = &head;
		for (int32_t i = 0; i < location; i++) {
			if (p->next == NULLPTR)
				return 0;
			//cout << p << endl;
			//cout << p->data << endl;
			p = p->next;
		}
		return p;
	}
	//头遍历
	node* traversal(node& head) {
		node* p = &head;
		for (; p->next != NULLPTR; p++) {
			//啥也没有
		}
		return p;
	}
};

int32_t main() {
	node head;
	head.initialization(head, 10);
	head.print(head);

	node* A1 = new node;
	node* A2 = new node;
	A1->next = A2;
	A2->previous = A1;
	A1->data = 10;
	A2->data = 20;
	A1->specifying_back_insert(15);
	cout << A1->next->data << endl;
	cout << A2->previous->data << endl;

	cout << endl;

	head.order_back_insert(head, 10, 110);
	head.print(head);

	A1->specifying_back_insert(A1, 40);
	cout << A1->next->data << endl;


	return 0;
}