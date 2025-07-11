#ifndef __BIT_LIB_
#define __BIT_LIB_

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std::string_literals;

namespace IMD {

	constexpr size_t BITS_PER_BYTE{ 8 };


	template<typename T>
	void print_bytes(const T& value, const std::string& separator = " "s) {
		auto ptr = reinterpret_cast<const std::byte*>(&value);
		for (size_t i{ 0 }; i < sizeof(T); ++i)
			std::cout << static_cast<short>(ptr[i]) << separator;
	}
	template<typename T>
	void println_bytes(const T& value, const std::string& separator = " "s) {
		print_bytes(value, separator);
		std::cout << std::endl;
	}

	template<typename T>
	void print_bits(const T& value, const std::string& separator = " "s) {
		auto ptr = reinterpret_cast<const std::byte*>(&value);
		for (size_t i{ 0 }; i < sizeof(T); ++i) {
			for (short j{ 7 }; j >= 0; --j)
				std::cout << (((static_cast<short>(ptr[i]) >> j) & 1));
			std::cout << separator;
		}
	}

	template<typename T>
	void println_bits(const T& value, const std::string& separator = " "s) {
		print_bits(value, separator);
		std::cout << std::endl;
	}

	template<typename T>
	void modify_byte(T& value, size_t index, std::byte new_byte) {
		if (index >= sizeof(T))
			throw std::runtime_error("Byte index is outside the size of the value");

		auto bytes = reinterpret_cast<std::byte*>(&value);
		bytes[index] = new_byte;
	}

	template<typename T>
	void modify_bit(T& value, size_t index, bool new_bit) {
		if (index >= sizeof(T) * BITS_PER_BYTE)
			throw std::runtime_error("Byte index is outside the size of the value");

		if (new_bit)
			value |= (T(1) << index);
		else
			value &= ~(T(1) << index);
	}

	template<typename T>
	bool compare_bytes(const T& first, const T& second) {
		return std::memcmp(&first, &second, sizeof(T)) == 0;
	}

	template<typename T>
	void swap_bytes(T& first, T& second) {
		auto ptr1 = reinterpret_cast<std::byte*>(&first);
		auto ptr2 = reinterpret_cast<std::byte*>(&second);

		for (size_t i{ 0 }; i < sizeof(T); ++i)
			std::swap(ptr1[i], ptr2[i]);
	}

	template<typename T>
	std::string bits_to_string(const T& value, const std::string& separator = " "s) {
		auto ptr = reinterpret_cast<const std::byte*>(&value);
		std::string result;

		result.reserve(sizeof(T) * BITS_PER_BYTE);

		for (size_t i{ 0 }; i < sizeof(T); ++i) {
			for (size_t j{ 0 }; j < BITS_PER_BYTE; ++j)
				result.append(std::to_string((static_cast<short>(ptr[i]) >> j) & 1));
			result.append(separator);
		}
		return result;
	}

	template<typename T>
	std::string bytes_to_string(const T& value, const std::string& separator = " "s) {
		auto ptr = reinterpret_cast<const std::byte*>(&value);
		std::string result;

		result.reserve(sizeof(T) * BITS_PER_BYTE);

		for (size_t i{ 0 }; i < sizeof(T); ++i) {
			result.append(std::to_string(static_cast<short>(ptr[i])));
			result.append(separator);
		}
		return result;
	}
}



#endif // !__BIT_LIB_
