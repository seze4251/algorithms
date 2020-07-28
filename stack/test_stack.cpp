#include "stack.h"
#include <iostream>


int main() {
	std::cout << "Starting Stack Tests" << std::endl;
	size_t capacity = 1;
	Stack<int> stack(capacity);
	stack.push(5);
	stack.push(19);
	assert(*stack.peek() == 19);
	assert(stack.pop() == 19);
	assert(stack.pop() == 5);
	// Yes I know these tests are horrible, but I am tired and will fix later
	std::cout << "Successfully ran all of Stack Tests" << std::endl;
	return 0;
}
