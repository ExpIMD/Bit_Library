#include "memory_library.h"
#include <vector>
#include <typeinfo>
#include <cstddef>

int main() {
	short a{1};

	IMD::println_bits(a);

	std::cout <<  std::boolalpha << IMD::any_bits_one(a);

}