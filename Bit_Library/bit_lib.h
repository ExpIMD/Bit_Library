#ifndef __BIT_LIB_
#define __BIT_LIB_

#include <iostream>
#include <cstddef>
#include <string>

namespace IMD {
	template<typename T>
	void print_bytes(const T& value, const std::string& separator = " "s) {
		auto ptr = reinterpret_cast<std::byte*>(&value);
		for (size_t i{ 0 }; i < sizeof(T); ++i)
			std::cout << static_cast<short>(*(ptr + i)) << separator;
	}
	template<typename T>
	void println_bytes(const T& value, const std::string& separator = " "s) {
		print_bytes(value, separator);
		std::cout << std::endl;
	}

}



#endif // !__BIT_LIB_
