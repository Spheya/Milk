#include "ServerStatus.hpp"

#include <sstream>

namespace milk {

	std::string ServerStatus::stringify() {
		std::stringstream stream;
		stream << "{\"version\":{\"name\":\"" << versionName << "\", \"protocol\" : " << protocolVersion << "}, \"players\" : {\"max\":" << maxPlayers <<
			", \"online\" : " << playerCount << ", \"sample\" : [] }, \"description\" : {\"text\":\"" << description << "\"}, \"enforcesSecureChat\" : " <<
			(enforcesSecureChat ? "true" : "false") << "}";
		return stream.str();
	}

}