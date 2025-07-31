#include <iostream>
#include <cstdint>

using namespace std;

class node {
public:
	int32_t num = 0;
	node* next = NULL;
};

bool linked_linked_insertion(node& head, int32_t location, int32_t data);
bool linked_linked_insertion(node* I_node, int32_t data);
bool hode_linked_insertion(node& head, int32_t location, int32_t data);
bool hode_linked_insertion(node* I_node, int32_t data);
bool linked_delete(node& head, int32_t location);
bool linked_delete(node* I_node);
node* linked_location_lookup(node& head, int32_t location);
node* linked_value_lookup(node& head, int32_t data);
int32_t linked_num_lookup(node& head, int32_t location);
int32_t linked_size(node& head);

int32_t main() {

	node linked;

	node* A1 = new node;
	linked.next = A1;
	node* A2 = new node;
	A1->next = A2;
	node* A3 = new node;
	A2->next = A3;
	node* A4 = new node;
	A3->next = A4;
	node* A5 = new node;
	A4->next = A5;
	node* A6 = new node;
	A5->next = A6;
	node* A7 = new node;
	A6->next = A7;
	node* A8 = new node;
	A7->next = A8;
	node* A9 = new node;
	A8->next = A9;
	node* A10 = new node;
	A9->next = A10;

	A1->num = 10;
	A2->num = 2;
	A3->num = 33;
	A4->num = 90;
	A5->num = 11;
	A6->num = 88;
	A7->num = 74;
	A8->num = 11;
	A9->num = 770;
	A10->num = 2;

	for (node* p = &linked; p != NULL; p = p->next)
		cout << p->num << endl;

	cout << endl;
	linked_linked_insertion(linked, 3, 10);
	for (node* p = &linked; p != NULL; p = p->next)
		cout << p->num << endl;

	cout << endl;
	linked_linked_insertion(A10, 10);
	for (node* p = &linked; p != NULL; p = p->next)
		cout << p->num << endl;

	cout << endl;
	hode_linked_insertion(linked, 8, 10);
	for (node* p = &linked; p != NULL; p = p->next)
		cout << p->num << endl;

	cout << endl;
	linked_delete(linked, 10);
	for (node* p = &linked; p != NULL; p = p->next)
		cout << p->num << endl;

	cout << endl;
	linked_delete(A2);
	for (node* p = &linked; p != NULL; p = p->next)
		cout << p->num << endl;

	cout << linked_location_lookup(linked, 10)->num << endl;
	cout << linked_value_lookup(linked, 10) << endl;
	cout << linked.next << endl;
	cout << linked_num_lookup(linked, 10) << endl;
	cout << linked_size(linked) << endl;

	node new_linked1; {
		node* new_linked_tail2 = &new_linked1;
		node* new_linked_tail1 = &new_linked1;
		for (int32_t i = 0; i < 10; i++) {
			new_linked_tail1 = new node;
			new_linked_tail1->num = i;
			new_linked_tail2->next = new_linked_tail1;
			new_linked_tail2 = new_linked_tail1;
		}
	}
	for (node* p = &new_linked1; p != NULL; p = p->next)
		cout << p->num << endl;
	cout << endl;
	node new_linked2; {
		node* new_linked_tail1 = &new_linked2;
		for (int32_t i = 0; i < 10; i++) {
			new_linked_tail1 = new node;
			new_linked_tail1->num = i;
			new_linked_tail1->next = new_linked2.next;
			new_linked2.next = new_linked_tail1;
		}
	}
	for (node* p = &new_linked2; p != NULL; p = p->next)
		cout << p->num << endl;

	return 0;
}



bool linked_linked_insertion(node* I_node, int32_t data) {
	if (I_node == NULL)
		return false;
	node* new_node = new node;
	new_node->next = I_node->next;
	I_node->next = new_node;
	new_node->num = data;
	//cout << I_node->num << endl;
	//cout << new_node->num << endl;
	return true;
}



bool linked_linked_insertion(node& head, int32_t location, int32_t data) {
	node* p = linked_location_lookup(head, location);
	//if (location < 1)
	//	return false;

	//for (int32_t i = 1; i < location; i++) {
	//	if (p->next == NULL)
	//		return false;
	//	p = p->next;
	//}
	return linked_linked_insertion(p, data);
}




bool hode_linked_insertion(node& head, int32_t location, int32_t data) {
	if (location < 1)
		return false;
	node* p = linked_location_lookup(head, location - 1);
	//node* p = &head;
	//for (int32_t i = 1; i < location - 1; i++) {
	//	if (p->next == NULL)
	//		return false;
	//	p = p->next;
	//}
	return hode_linked_insertion(p, data);
}



bool hode_linked_insertion(node* I_hode, int32_t data) {
	if (I_hode == NULL)
		return false;
	node* new_node = new node;
	new_node->num = I_hode->num;
	I_hode->num = data;
	new_node->next = I_hode->next;
	I_hode->next = new_node;
	return true;
}



bool linked_delete(node& head, int32_t location) {
	node* p = linked_location_lookup(head, location);
	//if (location < 1)
	//	return false;

	//for (int32_t i = 1; i < location - 1; i++) {
	//	if (p == NULL)
	//		return false;
	//	p = p->next;
	//}

	node* next = p->next->next;
	node* middle = p->next;
	delete middle;
	//delete p->next;
	p->next = next;
	return true;
}



bool linked_delete(node* I_node) {
	if (I_node == NULL)
		return false;
	I_node->num = I_node->next->num;
	node* middle = I_node->next;
	I_node->next = middle->next;
	delete middle;
	return true;
}



node* linked_location_lookup(node& head, int32_t location) {
	if (location < 1)
		return NULL;
	node* p = &head;

	for (int32_t i = 1; i < location; i++) {
		if (p == NULL)
			return NULL;
		p = p->next;
	}
	return p;
}



node* linked_value_lookup(node& head, int32_t data) {
	if (data < 1)
		return NULL;
	node* p = &head;
	for (int32_t i = 0; i < data; i++) {
		if (p == NULL)
			return NULL;
		p = p->next;
		if (p->num == data)
			return p;
	}
	return NULL;
}



int32_t linked_num_lookup(node& head, int32_t location) {
	if (location < 1)
		return 0;
	node* p = &head;
	int32_t num = 0;
	for (int32_t i = 0; i < location; i++) {
		if (p == NULL)
			return num;
		p = p->next;
		if (p->num == location)
			num++;
	}
	return num;
}



int32_t linked_size(node& head) {
	node* p = &head;
	int32_t num = 0;
	for (; p != NULL; p = p->next)
		num++;
	return num;
}