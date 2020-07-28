#include <exception>
#include <memory>
#include <stddef.h>
#include <stdlib.h>


// TODO: Look at std::stack and fix user facing API
//       Add missing methods, and adjust implementation to match theirs
//       Think about how to implement move semantics
// TODO: Look into a more C++ way to do realloc
// TODO: 100% UT coverage with google test, requires more of a build system than command line g++ lol


template <typename T>
class Stack {
public:
	Stack(size_t capacity, bool auto_resize=true)
		: capacity_(capacity), auto_resize_(auto_resize)
	{
		if (capacity == 0) {
			throw std::runtime_error("Cannot create a stack with 0 capacity");
		}

		// Cannot use make_unique b/c C++ doesn't support realloc
		// If you want to use realloc, you must use malloc for defined behavior
		stack_.reset(reinterpret_cast<T*>(malloc(capacity_*sizeof(T))));
	}

	void push(T data) {
		if (idx_ == capacity_) {
			if (!auto_resize_) {
				throw std::runtime_error("Stack is full and cannot alloc b/c auto_resize is set to false");
			}

			capacity_ = 2 * capacity_;
			stack_.reset(reinterpret_cast<T*>(realloc(stack_.release(), capacity_*sizeof(T))));

			if (!stack_) {
				throw std::runtime_error("Failed to realloc stack");
			}
		}

		stack_[idx_] = std::move(data);
		idx_++;
	}

	// Returns a pointer to the top element in the stack
	T* peek() {
		if (idx_ == 0) {
			return nullptr;
		}

		return &stack_[idx_-1];
	}

	// Returns the top element in the stack, and removes it from the stack
	T pop () {
		if (idx_ == 0) {
			throw std::runtime_error("Cannot get element b/c not elements are on stack");
		}
		return stack_[--idx_];
	}

private:
	std::unique_ptr<T[]> stack_; ///< Structure that holds the stack
	size_t idx_ = 0; ///< Index to insert into
	size_t capacity_; ///< Maximum # of T elements allowed on vector
	bool auto_resize_; ///< Allow users to get an exception instead of auto-resizing
};
