#include "bit_lib.h"

class item {
public:
	size_t field;
	item(size_t value) : field(value) {}
};

int main() {
	int a{ 278 };

	IMD::println_bytes(a);

	std::cout << IMD::bytes_to_string(a, "+++");


}