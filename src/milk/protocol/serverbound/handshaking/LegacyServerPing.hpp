#pragma once

#include "milk/protocol/ConnectionState.hpp"
#include "milk/protocol/Packet.hpp"

namespace milk {
	namespace serverbound {
		namespace handshaking {

			struct LegacyServerPing {
				static constexpr ConnectionState connectionState = ConnectionState::Handshaking;
				static constexpr int32_t packetId = 0xFE;

				static LegacyServerPing deserialize(Packet& packet) {
					return {};
				}
			};

		}
	}
}