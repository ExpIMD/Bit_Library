#include "bit_lib.h"

class item {
public:
	size_t field;
	item(size_t value) : field(value) {}
};

int main() {
	item a{ 2 };
	item b{ 9 };

	IMD::swap_bytes(a, b);

	std::cout << a.field;


}