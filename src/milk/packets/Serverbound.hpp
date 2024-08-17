#pragma once

#include <string>

#include "../ConnectionState.hpp"
#include "Packet.hpp"

namespace milk {
	namespace serverbound {

		struct Handshake {
			static constexpr ConnectionState connectionState = ConnectionState::HandShaking;
			static constexpr int32_t packetId = 0x00;

			int protocolVersion;
			std::string serverAdress;
			int16_t port;
			ConnectionState nextState;

			static Handshake deserialize(Packet& packet) {
				return {
					packet.readVarInt(),
					packet.readString(255),
					packet.readShort(),
					ConnectionState(packet.readVarInt())
				};
			}
		};

		struct LegacyServerPing {
			static constexpr ConnectionState connectionState = ConnectionState::HandShaking;
			static constexpr int32_t packetId = 0xFE;

			static LegacyServerPing deserialize(Packet& packet) {
				return {};
			}
		};

		struct StatusRequest {
			static constexpr ConnectionState connectionState = ConnectionState::Status;
			static constexpr int32_t packetId = 0x00;

			static StatusRequest deserialize(Packet& packet) {
				return {};
			}
		};

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

		struct LoginStart {
			static constexpr ConnectionState connectionState = ConnectionState::Login;
			static constexpr int32_t packetId = 0x00;

			std::string name;
			int64_t uuid1;
			int64_t uuid2;

			static LoginStart deserialize(Packet& packet) {
				return {
					packet.readString(16),
					packet.readLong(),
					packet.readLong()
				};
			}
		};
	}
}