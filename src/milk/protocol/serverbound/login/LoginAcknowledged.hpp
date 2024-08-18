#pragma once

#include "milk/protocol/ConnectionState.hpp"
#include "milk/protocol/Packet.hpp"

namespace milk {
	namespace serverbound {
		namespace login {

			struct LoginAcknowledged {
				static constexpr ConnectionState connectionState = ConnectionState::Login;
				static constexpr int32_t packetId = 0x03;

				static LoginAcknowledged deserialize(Packet& packet) {
					return {};
				}
			};

		}
	}
}