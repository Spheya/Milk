#pragma once

#include "milk/protocol/ConnectionState.hpp"
#include "milk/protocol/Packet.hpp"

namespace milk {
	namespace clientbound {
		namespace status {

			struct PingResponse {
				static constexpr ConnectionState connectionState = ConnectionState::Status;
				static constexpr int32_t packetId = 0x01;

				int64_t payload;

				Packet serialize() {
					Packet packet;
					packet.writeVarInt(packetId);
					packet.writeLong(payload);
					return packet;
				}
			};

		}
	}
}