#include <algorithm>
#include <iostream>
#include <limits>
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


void merge(std::vector<int>& vector, int p, int q, int r) {
	// Safety Checks
	if (p > q && q > r && vector.size() <= r) {
		std::cerr << "Bad inputs given to merge (p < q < r and r < vector.size) "
				<< "p: " << p << ", q: " << q << ", r:" << r << ", vector.size(): "
				<< vector.size() << std::endl;
	}

	std::vector<int> copy(vector);

	int i = 0;
	int j = 0;
	int i_len = q-p+1;
	int j_len = r-q;
	int j_idx = q+1;

	for (int k = p; k <= r; k++) {
		if (i == i_len) {
			vector[k] = copy[j_idx+j];
			j++;
		}
		else if (j == j_len) {
			vector[k] = copy[p+i];
			i++;
		}
		else {
			if (copy[p+i] < copy[j_idx+j]) {
				vector[k] = copy[p+i];
				i++;
			}
			else {
				vector[k] = copy[j_idx+j];
				j++;
			}
		}
	}
}

void merge_sort(std::vector<int>& vector, int p, int r) {
	if (p < r) {
		int q = (p + r) / 2;
		merge_sort(vector, p, q);
		merge_sort(vector, q+1, r);
		merge(vector, p, q, r);
	}
}


int main() {
	std::vector<int> my_vector = {5, 2, 4, 7, 1, 3, 2, 6};
	print_vector("my original vector", my_vector);
	merge_sort(my_vector, 0, 7);
	print_vector("my sorted vector", my_vector);
	return 0;
}
