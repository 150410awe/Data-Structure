#include <iostream>
#include <cstdint>

using namespace std;

#define NULLPTR nullptr

class stack {
public:
	bool input(int32_t stack_data) {
		input_prototype(stack_data);
		return true;
	}
	int32_t output(stack& stack_node) {
		return output_prototype(stack_node);
	}
	int32_t output(stack* stack_next) {
		return output_prototype(stack_next->next);
	}
	bool remove() {
		
	}
	int32_t data = 0;
	stack* next = NULLPTR;
private:
	void input_prototype(int32_t stack_data) {
		stack* i = this;
		for (; i->next != NULLPTR; i = i->next) {
			
		}
		stack* new_stack = new stack;
		new_stack->data = stack_data;
		i->next = new_stack;
	}
	int32_t output_prototype(stack& stack_node) {
		stack* stack_address = stack_node.next;
		for (stack* i = this; i->next != NULLPTR; i = i->next) {
			if (i->next == stack_address)
				return i->next->data;
		}
		return false;
	}
	int32_t output_prototype(stack* stack_next) {
		return traversal(stack_next)->data;
	}
	bool remove_prototype() {

	}
	stack* traversal(stack* stack_next) {
		for (stack* i = this; i->next != NULLPTR; i = i->next) {
			if (i->next == stack_next)
				return i;
		}
		return NULLPTR;
	}
	stack* traversal() {
		stack* i = this;
		for (; i->next != NULLPTR; i = i->next) {
		
		}
		return i;
	}
};


int32_t main() {
	stack linked;
	linked.input(10);
	cout << linked.output(linked.next) << endl;

	return 0;
}