#pragma once

#include "milk/protocol/ConnectionState.hpp"
#include "milk/protocol/Packet.hpp"

namespace milk {
	namespace clientbound {
		namespace configuration {

			struct FinishConfiguration {
				static constexpr ConnectionState connectionState = ConnectionState::Configuration;
				static constexpr int32_t packetId = 0x03;

				Packet serialize() {
					Packet packet;
					packet.writeVarInt(packetId);
					return packet;
				}
			};

		}
	}
}