#include <exception>
#include <memory>
#include <stddef.h>
#include <stdlib.h>

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
		// If you want to use realloc, you must use malloc
		stack_.reset(reinterpret_cast<T*>(malloc(capacity_*sizeof(T))));
	}

	void push(T data) {
		if (idx_ == capacity_) {
			capacity_ = 2 * capacity_;
			stack_.reset(reinterpret_cast<T*>(realloc(stack_.release(), capacity_*sizeof(T))));

			if (!stack_) {
				throw std::runtime_error("Failed to realloc stack");
			}
		}

		stack_[idx_] = std::move(data);
		idx_++;
	}


	T* peek() {
		return &stack_[idx_-1];

	}


	T pop () {
		if (idx_ == 0) {
			throw std::runtime_error("Cannot get element b/c not elements are on stack");
		}
		return stack_[--idx_];
	}

private:
	std::unique_ptr<T[]> stack_; ///< Structure that holds the stack
	size_t idx_ = 0; ///< Index to insert into
	size_t capacity_;
	bool auto_resize_;
};
