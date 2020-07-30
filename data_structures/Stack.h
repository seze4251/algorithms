#include <exception>
#include <memory>
#include <stddef.h>
#include <stdlib.h>


// TODO: Look into a more C++ way to do realloc
// TODO: 100% UT coverage with google test, requires more of a build system than command line g++ lol

// Ownership taking <sink>.
template <typename T>
class Stack {
public:
	Stack()
		: capacity_(1028)
	{
		stack_.reset(reinterpret_cast<T*>(malloc(capacity_*sizeof(T))));
	}

	Stack(size_t capacity)
		: capacity_(capacity)
	{
		if (capacity == 0) {
			throw std::runtime_error("Cannot create a stack with 0 capacity");
		}

		// Cannot use make_unique b/c C++ doesn't support realloc
		// If you want to use realloc, you must use malloc for defined behavior
		stack_.reset(reinterpret_cast<T*>(malloc(capacity_*sizeof(T))));
	}

	bool empty() {
		return idx_ == 0;
	}

	size_t size() {
		return idx_;
	}

	size_t capacity() {
		return capacity_;
	}

	void push(T& data) {
		resize();
		stack_[idx_] = data;
		idx_++;
	}

	void push(T&& data) {
		resize();
		stack_[idx_] = std::move(data);
		idx_++;
	}

	// Returns the top element in the stack, and removes it from the stack
	T pop () {
		if (idx_ == 0) {
			throw std::runtime_error("Cannot get element b/c no elements are on the stack");
		}
		return std::move(stack_[--idx_]);
	}

private:
	void resize() {
		if (idx_ == capacity_) {
			capacity_ = 2 * capacity_;
			stack_.reset(reinterpret_cast<T*>(realloc(stack_.release(), capacity_*sizeof(T))));

			if (!stack_) {
				throw std::runtime_error("Failed to realloc stack");
			}
		}
	}

	std::unique_ptr<T[]> stack_; ///< Structure that holds the stack
	size_t idx_ = 0; ///< Index to insert into
	size_t capacity_; ///< Maximum # of T elements allowed on vector
};
