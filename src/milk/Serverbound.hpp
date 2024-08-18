#pragma once

#include <string>

#include "ConnectionState.hpp"
#include "Packet.hpp"

namespace milk {
	namespace serverbound {

		struct Handshake {
			static constexpr ConnectionState connectionState = ConnectionState::HandShaking;
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
			UUID uuid;

			static LoginStart deserialize(Packet& packet) {
				return {
					packet.readString(16),
					packet.readUUID()
				};
			}
		};

		struct LoginAcknowledged {
			static constexpr ConnectionState connectionState = ConnectionState::Login;
			static constexpr int32_t packetId = 0x03;

			static LoginAcknowledged deserialize(Packet& packet) {
				return {};
			}
		};

		struct AcknowledgeFinishConfiguration {
			static constexpr ConnectionState connectionState = ConnectionState::Configuration;
			static constexpr int32_t packetId = 0x03;

			static AcknowledgeFinishConfiguration deserialize(Packet& packet) {
				return {};
			}
		};
	}
}