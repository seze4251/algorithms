#include <exception>
#include <functional>
#include <memory>
#include <stddef.h>
#include <stdlib.h>


template <typename Key, typename Value>
class HashTable {
public:
	HashTable(size_t capacity) : capacity_(capacity) {
		if (capacity_ == 0) {
			throw std::runtime_error("Cannot initialize HashTable with NULL capacity");
		}

		hash_table_ = std::make_unique<Bucket[]>(capacity_);

		// initialize all Bucket data members to nullptr
		for (int i = 0; i < capacity_; i++) {
			hash_table_[i].data = nullptr;
		}
	}

	// TODO Figure out copy/move semantics
	void insert(Key key, Value value) {
		if (++size_ == capacity_) {
			rehash();
		}

		size_t idx = std::hash(key) % capacity_;
		for (int i = 0; i < capacity_; i++) {
			if (!hash_table_[idx].data) {
				hash_table_[idx].key  = key;
				hash_table_[idx].data = std::make_unique(value);
				break;
			}
			idx = getNextIndex(idx, capacity_);
		}
	}

	void erase(Key key) {
		size_t idx = std::hash(key) % capacity_;
		for (int i = 0; i < capacity_ -1; i++) {
			if (hash_table_[idx].key == key) {
				hash_table_[idx].data.reset();
				return;
			}
			idx = getNextIndex(idx, capacity_);
		}

		std::runtime_error("Cannot delete key because it doesn't exist in table");
	}

	Value get(Key key) {
		size_t idx = std::hash(key) % capacity_;
		for (int i = 0; i < capacity_ -1; i++) {
			if (hash_table_[idx].key == key) {
				return hash_table_[idx].value;
			}
			idx = getNextIndex(idx, capacity_);
		}

		std::runtime_error("Cannot delete key because it doesn't exist in table");
	}

private:
	class Bucket {
	public:
		Key key;
		std::unique_ptr<Value> data;
	};

	void rehash() {
		// Create New Array
		size_t new_capacity = capacity_ * 2;
		std::unique_ptr<Bucket[]> new_hash_table = std::make_unique<Bucket[]>(new_capacity);

		// Zero out data members
		for (int i = 0; i < capacity_; i++) {
			hash_table_[i].data = nullptr;
		}

		// Move over contents
		for (int i = 0; i < capacity_; i++) {
			if (hash_table_[i].data != nullptr) {
				size_t new_idx = std::hash(hash_table_[i].key) % new_capacity;
				for (int j = 0; j < new_capacity; j++) {
					if (!new_hash_table[new_idx].data) {
						new_hash_table[new_idx].key = hash_table_[i].key;
						new_hash_table[new_idx].data = std::move(hash_table_[i].data);
					}
					new_idx = getNextIndex(new_idx, new_capacity);
				}
			}
		}

		// Swap tables, old table gets destroyed by going out of scope
		hash_table_.swap(new_hash_table);
		capacity_ = new_capacity;
	}

	size_t getNextIndex(size_t idx, size_t capacity) {
		return (idx + 1 == capacity) ? 0 : idx + 1;
	}

	std::unique_ptr<Bucket[]> hash_table_;
	size_t capacity_;
	size_t size_ = 0;
};
