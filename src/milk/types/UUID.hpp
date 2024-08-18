#pragma once

#include <cstdint>
#include <string>

namespace milk {

	struct UUID {
		uint64_t components[2];
		std::string stringify();
	};

}