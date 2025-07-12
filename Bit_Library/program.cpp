#include "bit_lib.h"
#include <vector>

class item {
public:
	size_t field;
	item(size_t value) : field(value) {}
};

int main() {
	int a{ 279 };

	auto temp = IMD::bytes_to_container<>(a);

	for (const auto& x : temp)
		std::cout << x << " ";

	std::cout << std::endl;
	

	std::cout << IMD::bytes_to_string(a, " ");


}