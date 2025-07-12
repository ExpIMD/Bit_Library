#include "bit_lib.h"
#include <vector>
#include <typeinfo>
#include <cstddef>
#include <list>

class item {
public:
	unsigned char data;

	item() : data(0x04) {}
};

int main() {
	
	std::list<std::byte> lst{ std::byte(123), std::byte(0), std::byte(0), std::byte(0) };
	
	auto i = IMD::restore_value<int>(lst.begin(), lst.end());

	IMD::print_oct_bytes(i);

	std::cout << i;

	return 0;

}