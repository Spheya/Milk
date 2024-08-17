#pragma once

#include <cstdint>

namespace milk {

	enum class ConnectionState : int32_t {
		HandShaking = 0,
		Status = 1,
		Login = 2,
		Transfer = 3
	};

}