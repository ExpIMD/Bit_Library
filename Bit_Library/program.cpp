#include "bit_lib.h"
#include <vector>
#include <typeinfo>

class item {
public:
	item() {}
};

int main() {
	short a{ 254 };
	IMD::println_bits(a);

	IMD::modify_bit(a, 12, 1);

	IMD::println_bits(a);


}