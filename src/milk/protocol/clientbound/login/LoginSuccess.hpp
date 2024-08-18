#pragma once

#include "milk/protocol/ConnectionState.hpp"
#include "milk/protocol/Packet.hpp"

namespace milk {
	namespace clientbound {
		namespace login {

			struct LoginSuccess {
				static constexpr ConnectionState connectionState = ConnectionState::Login;
				static constexpr int32_t packetId = 0x02;

				UUID uuid;
				std::string username;

				Packet serialize() {
					Packet packet;
					packet.writeVarInt(packetId);
					packet.writeUUID(uuid);
					packet.writeString(username, 16);
					packet.writeVarInt(0);
					packet.writeBool(false);
					return packet;
				}
			};

		}
	}
}