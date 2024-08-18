#pragma once

#include <cstdint>

namespace milk {

	enum class ConnectionState : uint8_t {
		Handshaking, Status, Login, Configuration, Play
	};

}