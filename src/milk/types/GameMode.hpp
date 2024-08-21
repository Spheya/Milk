#pragma once

#include <cstdint>

namespace milk {

	enum class GameMode : uint8_t {
		Survival = 0, Creative = 1, Adventure = 2, Spectator = 3
	};

}