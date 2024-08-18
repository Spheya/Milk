#pragma once

#include <string>

#include "Packet.hpp"
#include "ConnectionState.hpp"

namespace milk {
	namespace clientbound {

		struct StatusResponse {
			static constexpr ConnectionState connectionState = ConnectionState::Status;
			static constexpr int32_t packetId = 0x00;

			std::string jsonResponse;

			Packet serialize() {
				Packet packet;
				packet.writeVarInt(packetId);
				packet.writeString(jsonResponse, 32767);
				return packet;
			}
		};

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

		struct LoginSuccess {
			static constexpr ConnectionState connectionState = ConnectionState::Login;
			static constexpr int32_t packetId = 0x02;

			UUID uuid;
			std::string username;

			Packet serialize() {
				Packet packet;
				packet.writeVarInt(packetId);
				packet.writeUUID(uuid);
				packet.writeString(username, 16);
				packet.writeVarInt(0);
				packet.writeBool(false);
				return packet;
			}
		};

		struct FinishConfiguration {
			static constexpr ConnectionState connectionState = ConnectionState::Configuration;
			static constexpr int32_t packetId = 0x03;

			Packet serialize() {
				Packet packet;
				packet.writeVarInt(packetId);
				return packet;
			}
		};

		struct ChunkBatchFinished {
			static constexpr ConnectionState connectionState = ConnectionState::Play;
			static constexpr int32_t packetId = 0x0C;

			int32_t batchSize;

			Packet serialize() {
				Packet packet;
				packet.writeVarInt(packetId);
				packet.writeVarInt(batchSize);
				return packet;
			}
		};

		struct ChunkBatchStart {
			static constexpr ConnectionState connectionState = ConnectionState::Play;
			static constexpr int32_t packetId = 0x0D;

			Packet serialize() {
				Packet packet;
				packet.writeVarInt(packetId);
				return packet;
			}
		};

	}
}