#include "stack.h"
#include <iostream>


int main() {
	size_t capacity = 1;
	Stack<int> stack(capacity);
	stack.push(5);
	stack.push(19);
	assert(*stack.peek() == 19);
	assert(stack.pop() == 19);
	assert(stack.pop() == 5);
	return 0;
}
