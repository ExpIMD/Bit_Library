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
	int a{9};
	int b{-9};

	IMD::println_bin_bytes(a);
	IMD::println_bin_bytes(b);

}