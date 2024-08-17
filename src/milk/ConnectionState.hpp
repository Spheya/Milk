#pragma once

#include <cstdint>

namespace milk {

	enum class ConnectionState : uint8_t {
		HandShaking, Status, Login, Configuration, Play
	};

}