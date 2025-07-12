#include "bit_lib.h"
#include <vector>
#include <typeinfo>

class item {
public:
	unsigned char data;

	item() : data(0x04) {}
};

int main() {
	item a{};
	IMD::println_bits(a);
	std::cout << std::boolalpha << IMD::is_power_of_two(a);


}