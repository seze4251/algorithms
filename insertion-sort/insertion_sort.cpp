#include <iostream>
#include <string>
#include <vector>


void print_vector(std::string msg, std::vector<int>& vector) {
	std::cout << msg << std::endl;
	std::cout << "Vector: <";
	for (auto& value : vector) {
		std::cout << value;
		if (&value != &vector.back()) {
			std::cout << ", ";
		}
	}
	std::cout << ">" << std::endl;;
}


void insertion_sort_ascending(std::vector<int>& vector) {
	for (int j = 1; j < vector.size(); j++) {
		int key = vector[j];
		int i = j - 1;
		while (i >= 0 && vector[i] > key) {
			vector[i+1] = vector[i];
			i--;
		}
		vector[i+1] = key;
	}
}


int linear_search(int value, std::vector<int>& vector) {
	for (int i = 0; i < vector.size(); i++) {
		if (vector[i] == value) {
			return i;
		}
	}

	return -1;
}


/*
 * Difference is we switch the inner while loop greater than > to less than <
 */
void insertion_sort_descending(std::vector<int>& vector) {
	for (int j = 1; j < vector.size(); j++) {
		int key = vector[j];
		int i = j - 1;
		while (i >= 0 && vector[i] < key) {
			vector[i+1] = vector[i];
			i--;
		}
		vector[i+1] = key;
	}
}


int main() {
	std::vector<int> my_vector{5, 1, 4, 10, 4, 7, 8, 7, 22};
	print_vector("Initial Vector Print:", my_vector);
	insertion_sort_ascending(my_vector);
	print_vector("Outer Sorted Vector Ascending", my_vector);
	insertion_sort_descending(my_vector);
	print_vector("Sorted Vector Descending", my_vector);
	std::vector<int> search_vector{5, 1, 4, 10, 4, 7, 8, 7, 22};
	assert(linear_search(7, search_vector) == 5);
	assert(linear_search(100, search_vector) == -1);
	return 0;
}
