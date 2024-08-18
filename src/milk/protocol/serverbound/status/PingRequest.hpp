#pragma once

#include "milk/protocol/ConnectionState.hpp"
#include "milk/protocol/Packet.hpp"

namespace milk {
	namespace serverbound {
		namespace status {

			struct PingRequest {
				static constexpr ConnectionState connectionState = ConnectionState::Status;
				static constexpr int32_t packetId = 0x01;

				int64_t payload;

				static PingRequest deserialize(Packet& packet) {
					return {
						packet.readLong()
					};
				}
			};

		}
	}
}