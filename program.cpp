#include "bit_lib.h"
#include <vector>
#include <typeinfo>
#include <cstddef>

int main() {
	int a{314};
	
	std::cout << (a >> 3);

	IMD::shift_right_bits(a, 3);

	std::cout << a;

}