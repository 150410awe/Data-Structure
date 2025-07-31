#include <iostream>
#include <cstdint>

using namespace std;

class node {
public:
	int32_t num = 0;
	node* next = NULL;
};

bool initialization_linked(class node *head_pointer);
bool linked_empty(class node* node);

int32_t main() {
	node head;
	initialization_linked(&head);
	cout << linked_empty(&head) << endl;



	return 0;
}



bool linked_empty(class node* node) {
	if (node->next == NULL)
		return true;
	else
		return false;
}