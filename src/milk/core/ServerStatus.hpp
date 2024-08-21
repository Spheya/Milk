#pragma once

#include "Core.hpp"

#include <string>

namespace milk {

	struct ServerStatus {
		std::string versionName = MILK_MINECRAFT_VERSION;
		int protocolVersion = MILK_PROTOCOL_VERSION;

		int playerCount = 0;
		int maxPlayers = 0;

		std::string description = "a milk server";
		bool enforcesSecureChat = false;

		std::string stringify();
	};

}