# Memory Library
This library provides utilities for inspecting and manipulating the raw byte and bit representation of arbitrary objects in memory.
The library does not interpret padding bits or bitfields; it operates on the raw bytes.

# Special notes
## Why std::byte instead of unsigned char?
std::byte, introduced in C++17, is a distinct type designed specifically to represent raw memory without implying any numeric meaning or arithmetic operations.
Unlike unsigned char, which is an integral type and can be used in arithmetic, std::byte clearly signals intent: we are working with raw memory bytes, not numeric values.

## Bit numbering
This library treats the object memory as a contiguous array of bytes in little-endian order. Bits within each byte are numbered from right to left (from the least significant bit at position 0 on the right, to the most significant bit at position 7 on the left).
