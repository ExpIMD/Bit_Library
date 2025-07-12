#include "bit_lib.h"
#include <vector>
#include <typeinfo>

class item {
public:
	item() {}
};

int main() {
	item a{  };

	size_t s;

	IMD::print_bits(a);


}