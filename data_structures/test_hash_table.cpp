#include "HashTable.h"
#include <iostream>
#include <string>


int main() {
	std::cout << "Starting HashTable Tests" << std::endl;
	HashTable<std::string, std::string> hash_table(10);

	std::cout << "Successfully ran all of HashTable Tests" << std::endl;
	return 0;
}
