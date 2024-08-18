#pragma once

#include "milk/protocol/ConnectionState.hpp"
#include "milk/protocol/Packet.hpp"

namespace milk {
	namespace serverbound {
		namespace login {

			struct LoginStart {
				static constexpr ConnectionState connectionState = ConnectionState::Login;
				static constexpr int32_t packetId = 0x00;

				std::string name;
				UUID uuid;

				static LoginStart deserialize(Packet& packet) {
					return {
						packet.readString(16),
						packet.readUUID()
					};
				}
			};

		}
	}
}