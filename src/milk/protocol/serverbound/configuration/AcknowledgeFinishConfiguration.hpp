#pragma once

#include "milk/protocol/ConnectionState.hpp"
#include "milk/protocol/Packet.hpp"

namespace milk {
	namespace serverbound {
		namespace configuration {

			struct AcknowledgeFinishConfiguration {
				static constexpr ConnectionState connectionState = ConnectionState::Configuration;
				static constexpr int32_t packetId = 0x03;

				static AcknowledgeFinishConfiguration deserialize(Packet& packet) {
					return {};
				}
			};

		}
	}
}