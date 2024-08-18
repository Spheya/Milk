#pragma once

#include "milk/protocol/ConnectionState.hpp"
#include "milk/protocol/Packet.hpp"

namespace milk {
	namespace clientbound {
		namespace status {

			struct StatusResponse {
				static constexpr ConnectionState connectionState = ConnectionState::Status;
				static constexpr int32_t packetId = 0x00;

				std::string jsonResponse;

				Packet serialize() {
					Packet packet;
					packet.writeVarInt(packetId);
					packet.writeString(jsonResponse, 32767);
					return packet;
				}
			};

		}
	}
}