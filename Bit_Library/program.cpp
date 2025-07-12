#include "bit_lib.h"
#include <vector>

class item {
public:
	size_t field;
	item(size_t value) : field(value) {}
};

int main() {
	item a{ 12 };

	IMD::println_bits(a);

	IMD::invert_bits(a);

	IMD::println_bits(a);


}