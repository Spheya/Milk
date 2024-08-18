#pragma once

#include "milk/protocol/ConnectionState.hpp"
#include "milk/protocol/Packet.hpp"

namespace milk {
	namespace serverbound {
		namespace status {

			struct StatusRequest {
				static constexpr ConnectionState connectionState = ConnectionState::Status;
				static constexpr int32_t packetId = 0x00;

				static StatusRequest deserialize(Packet& packet) {
					return {};
				}
			};

		}
	}
}