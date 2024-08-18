#include "UUID.hpp"

#include <sstream>

std::string milk::UUID::stringify() {
	std::stringstream stream;
	stream << std::hex;
	stream << ((components[0] >> 32) & 0xFFFFFFFFull) << '-';
	stream << ((components[0] >> 16) & 0xFFFFull) << '-';
	stream << ((components[0] >>  0) & 0xFFFFull) << '-';
	stream << ((components[1] >> 48) & 0xFFFFull) << '-';
	stream << ((components[1] >>  0) & 0xFFFFFFFFFFFFull);
	return stream.str();
}
