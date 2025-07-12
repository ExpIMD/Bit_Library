#ifndef __BIT_LIB_
#define __BIT_LIB_

#include <algorithm>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std::string_literals;

namespace IMD {

	// The number of bits in one byte
	constexpr size_t BITS_PER_BYTE{ 8 };

	// Returns the number of bytes of the specified type <T>
	template<typename T>
	constexpr size_t byte_count() noexcept {
		return sizeof(T);
	}

	// Returns the number of bits of the specified type <T>
	template<typename T>
	constexpr size_t bit_count() noexcept {
		return sizeof(T) * BITS_PER_BYTE;
	}

	// Prints the bytes of <value> in hexadecimal format without a trailing newline
	template<typename T>
	void print_hex_bytes(const T& value, const std::string& separator = " "s) {
		auto ptr = reinterpret_cast<const std::byte*>(&value);
		for (size_t i{ 0 }; i < sizeof(T); ++i)
			std::cout << "0x" << std::setw(2) << std::setfill('0') << std::hex << static_cast<short>(static_cast<unsigned char>(ptr[i])) << separator;
	}

	// Prints the bytes of <value> in decimal format without a trailing newline
	template<typename T>
	void print_dec_bytes(const T& value, const std::string& separator = " "s) {
		auto ptr = reinterpret_cast<const std::byte*>(&value);
		for (size_t i{ 0 }; i < sizeof(T); ++i)
			std::cout << static_cast<short>(static_cast<unsigned char>(ptr[i])) << separator;
	}

	// Prints the bytes of <value> in octal format without a trailing newline
	template<typename T>
	void print_oct_bytes(const T& value, const std::string& separator = " "s) {
		auto ptr = reinterpret_cast<const std::byte*>(&value);
		for (size_t i{ 0 }; i < sizeof(T); ++i)
			std::cout << "0" << std::setw(3) << std::setfill('0') << std::oct << static_cast<short>(static_cast<unsigned char>(ptr[i])) << separator;
	}

	// Prints the bytes of <value> in binary format without a trailing newline
	template<typename T>
	void print_bin_bytes(const T& value, const std::string& separator = " "s){
		auto ptr = reinterpret_cast<const std::byte*>(&value);
		for (size_t i{ 0 }; i < sizeof(T); ++i) {
			unsigned char byte = static_cast<unsigned char>(ptr[i]);
			std::cout << "0b";
			for (size_t j{BITS_PER_BYTE}; j-- > 0; )
				std::cout << ((byte >> j) & 1);
			std::cout << separator;
		}
	}

	// Print the bits of <value> without a trailing newline
	template<typename T>
	void print_bits(const T& value, const std::string& separator = " "s) {
		auto ptr = reinterpret_cast<const std::byte*>(&value);
		for (size_t i{ 0 }; i < sizeof(T); ++i) {
			for (size_t j{ BITS_PER_BYTE }; j-- > 0; )
				std::cout << (((static_cast<unsigned char>(ptr[i]) >> j) & 1));
			std::cout << separator;
		}
	}

	// Prints the bytes of <value> in hexadecimal format followed by a newline
	template<typename T>
	void println_hex_bytes(const T& value, const std::string& separator = " "s) {
		print_hex_bytes(value, separator);
		std::cout << std::endl;
	}

	// Prints the bytes of <value> in decimal format followed by a newline
	template<typename T>
	void println_dec_bytes(const T& value, const std::string& separator = " "s) {
		print_dec_bytes(value, separator);
		std::cout << std::endl;
	}
	
	// Prints the bytes of <value> in octal format followed by a newline
	template<typename T>
	void println_oct_bytes(const T& value, const std::string& separator = " "s) {
		print_oct_bytes(value, separator);
		std::cout << std::endl;
	}

	// Prints the bytes of <value> in binary format followed by a newline
	template<typename T>
	void println_bin_bytes(const T& value, const std::string& separator = " "s){
		print_bin_bytes(value, separator);
		std::cout << std::endl;
	}

	// Prints the bits of <value> followed by a newline
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

	// Changes the bit of the supplied <value> at the specified <index> to <new_bit>
	template<typename T>
	void modify_bit(T& value, size_t index, bool new_bit) {
		if (index >= sizeof(T) * BITS_PER_BYTE)
			throw std::runtime_error("Byte index is outside the size of the value");

		auto ptr = reinterpret_cast<std::byte*>(&value);
		size_t byte_index{ index / BITS_PER_BYTE };
		size_t bit_index{ index % BITS_PER_BYTE };

		auto byte = static_cast<unsigned char>(ptr[byte_index]);
		if (new_bit)
			byte |= (1 << bit_index);
		else
			byte &= ~(1 << bit_index);

		ptr[byte_index] = static_cast<std::byte>(byte);
	}

	// Compares the bytes of two values <first> and <second>
	template<typename T>
	int compare_bytes(const T& first, const T& second) {
		return memcmp(&first, &second, sizeof(T));
	}

	// Swaps the bytes of the given values: <first> and <second>
	template<typename T>
	void swap_bytes(T& first, T& second) {
		auto ptr1 = reinterpret_cast<std::byte*>(&first);
		auto ptr2 = reinterpret_cast<std::byte*>(&second);

		for (size_t i{ 0 }; i < sizeof(T); ++i)
			std::swap(ptr1[i], ptr2[i]);
	}

	// Returns a string representation of the bytes of <value> with a <separator>
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

	// Returns a string representation of the bits of <value> with a <separator>
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

	// Converts the bytes of <value> into a container
	template<typename T, typename C = std::vector<short>>
	C bytes_to_container(const T& value) {
		auto ptr = reinterpret_cast<const std::byte*>(&value);

		C container{};
		auto it = std::back_inserter(container);

		for (size_t i{ 0 }; i < sizeof(T); ++i)
			*it = static_cast<typename C::value_type>(static_cast<unsigned char>(ptr[i]));

		return container;
	}

	// Converts the bits of <value> into a container
	template<typename T, typename C = std::vector<bool>>
	C bits_to_container(const T& value) {
		auto ptr = reinterpret_cast<const std::byte*>(&value);

		C container{};
		auto it = std::back_inserter(container);

		for (size_t i{ 0 }; i < sizeof(T); ++i)
			for (size_t j{ 0 }; j < BITS_PER_BYTE; ++j)
				*it = (static_cast<unsigned char>(ptr[i]) >> j) & 1;

		return container;
	}

	// Inverts (bitwise NOT) all bits in <value>
	template<typename T>
	void invert_bits(T& value) {
		auto ptr = reinterpret_cast<std::byte*>(&value);

		for (size_t i{ 0 }; i < sizeof(T); ++i)
			ptr[i] = static_cast<std::byte>(~static_cast<unsigned char>(ptr[i]));
	}

	// Return the number of bits set to 1 in <value>
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

	// Return the number of bits set to 0 in <value>
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

	// Returns true if <value> has exactly one bit set to 1, indicating it is a power of two
	template<typename T>
	bool is_power_of_two(const T& value) {
		auto ptr = reinterpret_cast<const std::byte*>(&value);
		size_t one_bit_count{ 0 };

		for (size_t i{ 0 }; i < sizeof(T); ++i) {
			auto byte = static_cast<unsigned char>(ptr[i]);
			while (byte) {
				one_bit_count += (byte & 1);
				byte >>= 1;

				if (one_bit_count > 1)
					return false;
			}
		}

		return one_bit_count == 1;
	}

	// Restores a value of type <T> from a sequence of bytes in the range [first, last)
	template <typename T, typename InputIt>
	T restore_value(InputIt first, InputIt last) {
		if (std::distance(first, last) < sizeof(T))
			throw std::runtime_error("Not enough bytes to restore value");

		T value;
		auto ptr = reinterpret_cast<std::byte*>(&value);
		for (size_t i{ 0 }; i < sizeof(T); ++i, ++first)
			ptr[i] = static_cast<std::byte>(*first);

		return value;
	}

	// Reverses the byte order of a value of type <T> in place
	template<typename T>
	void byte_swap(T& value) {
		auto ptr = reinterpret_cast<std::byte*>(&value);

		for (size_t i {0}; i < sizeof(T) / 2; ++i)
			std::swap(ptr[i], ptr[sizeof(T) - 1 - i]);
	}
}



#endif // !__BIT_LIB_
