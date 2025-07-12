#ifndef __BIT_LIB_
#define __BIT_LIB_

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std::string_literals;

namespace IMD {

	constexpr size_t BITS_PER_BYTE{ 8 }; // The number of bits in one byte

	// Returns the number of bytes of the specified type
	template<typename T>
	constexpr size_t byte_count() noexcept {
		return sizeof(T);
	}

	// Returns the number of bits of the specified type
	template<typename T>
	constexpr size_t bit_count() noexcept {
		return sizeof(T) * BITS_PER_BYTE;
	}

	// Prints to console the byte sequence for a given <value> without a new line
	template<typename T>
	void print_bytes(const T& value, const std::string& separator = " "s) {
		auto ptr = reinterpret_cast<const std::byte*>(&value);
		for (size_t i{ 0 }; i < sizeof(T); ++i)
			std::cout << static_cast<short>(ptr[i]) << separator;
	}

	// Prints to console the byte sequence for a given <value> with a new line
	template<typename T>
	void println_bytes(const T& value, const std::string& separator = " "s) {
		print_bytes(value, separator);
		std::cout << std::endl;
	}

	// Prints to console the bit sequence for a given value without a new line
	template<typename T>
	void print_bits(const T& value, const std::string& separator = " "s) {
		auto ptr = reinterpret_cast<const std::byte*>(&value);
		for (size_t i{ 0 }; i < sizeof(T); ++i) {
			for (size_t j{ BITS_PER_BYTE }; j-- > 0; )
				std::cout << (((static_cast<int>(ptr[i]) >> j) & 1));
			std::cout << separator;
		}
	}

	// Prints to console the bit sequence for a given <value> with a new line
	template<typename T>
	void println_bits(const T& value, const std::string& separator = " "s) {
		print_bits(value, separator);
		std::cout << std::endl;
	}

	// Changes the byte of the supplied <value> with the specified <index>
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

		auto ptr = reinterpret_cast<std::byte*>(&value);
		size_t byte_index{ index / BITS_PER_BYTE };
		size_t bit_index{ index % BITS_PER_BYTE };

		unsigned char byte = static_cast<unsigned char>(ptr[byte_index]);
		if (new_bit)
			byte |= (1 << bit_index);
		else
			byte &= ~(1 << bit_index);

		ptr[byte_index] = static_cast<std::byte>(byte);
	}

	template<typename T>
	bool compare_bytes(const T& first, const T& second) {
		return std::memcmp(&first, &second, sizeof(T)) == 0;
	}

	// Swaps the bytes of the given values: <first> and <second>
	template<typename T>
	void swap_bytes(T& first, T& second) {
		auto ptr1 = reinterpret_cast<std::byte*>(&first);
		auto ptr2 = reinterpret_cast<std::byte*>(&second);

		for (size_t i{ 0 }; i < sizeof(T); ++i)
			std::swap(ptr1[i], ptr2[i]);
	}

	// Returns a string representation of the bits of the specified <value> with a <separator>
	template<typename T>
	std::string bits_to_string(const T& value, const std::string& separator = " "s) {
		auto ptr = reinterpret_cast<const std::byte*>(&value);
		std::string result;

		result.reserve(sizeof(T) * BITS_PER_BYTE);

		for (size_t i{ 0 }; i < sizeof(T); ++i) {
			for (size_t j{ 0 }; j < BITS_PER_BYTE; ++j)
				result.append(std::to_string((static_cast<unsigned char>(ptr[i]) >> j) & 1));
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
			result.append(std::to_string(static_cast<unsigned char>(ptr[i])));
			result.append(separator);
		}
		return result;
	}

	template<typename T, typename C = std::vector<bool>>
	C bits_to_container(const T& value) {
		auto ptr = reinterpret_cast<const std::byte*>(&value);

		C container{};
		auto it = std::back_inserter(container);

		for (size_t i{ 0 }; i < sizeof(T); ++i) {
			for (size_t j{ 0 }; j < BITS_PER_BYTE; ++j)
				*it = (static_cast<unsigned char>(ptr[i]) >> j) & 1;
		}

		return container;
	}

	template<typename T, typename C = std::vector<unsigned char>>
	C bytes_to_container(const T& value) {
		auto ptr = reinterpret_cast<const std::byte*>(&value);
		C container{};

		auto it = std::back_inserter(container);

		for (size_t i{ 0 }; i < sizeof(T); ++i)
			*it = static_cast<unsigned char>(ptr[i]);

		return container;
	}

	template<typename T>
	void invert_bits(T& value) {
		auto ptr = reinterpret_cast<std::byte*>(&value);

		for (size_t i{ 0 }; i < sizeof(T); ++i)
			ptr[i] = static_cast<std::byte>(~static_cast<unsigned char>(ptr[i]));
	}

	template<typename T>
	size_t one_bit_count(const T& value) {
		auto ptr = reinterpret_cast<const std::byte*>(&value);
		size_t count{ 0 };

		for (size_t i{ 0 }; i < sizeof(T); ++i) {
			auto byte = static_cast<unsigned char>(ptr[i]);
			while (byte) {
				count += byte & 1;
				byte >>= 1;
			}
		}

		return count;
	}

	template<typename T>
	size_t zero_bit_count(const T& value) {
		auto ptr = reinterpret_cast<const std::byte*>(&value);
		size_t count{ 0 };

		for (size_t i{ 0 }; i < sizeof(T); ++i) {
			auto byte = static_cast<unsigned char>(ptr[i]);
			for (unsigned char j{ 0 }; j < BITS_PER_BYTE; ++j)
				if ((byte & (1 << j)) == 0)
					++count;
		}

		return count;
	}

	template<typename T>
	bool is_power_of_two(const T& value) {
		// TODO: реализация
	}








}



#endif // !__BIT_LIB_
