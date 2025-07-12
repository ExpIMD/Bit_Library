#include "bit_lib.h"
#include <vector>
#include <typeinfo>
#include <cstddef>

int main() {
	int a{314};
	
	IMD::println_dec_bytes(a);

	auto c = IMD::bytes_to_container(a);

	for(auto x : c)
		std::cout << std::hex << x << " ";

}