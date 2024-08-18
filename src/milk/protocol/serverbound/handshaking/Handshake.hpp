#pragma once

#include "milk/protocol/ConnectionState.hpp"
#include "milk/protocol/Packet.hpp"

namespace milk {
	namespace serverbound {
		namespace handshaking {

			struct Handshake {
				static constexpr ConnectionState connectionState = ConnectionState::Handshaking;
				static constexpr int32_t packetId = 0x00;

				enum class NextState : int32_t {
					Status = 1, Login = 2, Transfer = 3
				};

				int protocolVersion;
				std::string serverAdress;
				int16_t port;
				NextState nextState;

				static Handshake deserialize(Packet& packet) {
					return {
						packet.readVarInt(),
						packet.readString(255),
						packet.readShort(),
						NextState(packet.readVarInt())
					};
				}
			};

		}
	}
}