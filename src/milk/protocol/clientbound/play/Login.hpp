#pragma once

#include "milk/protocol/ConnectionState.hpp"
#include "milk/protocol/Packet.hpp"
#include "milk/types/GameMode.hpp"
#include "milk/core/Math.hpp"

namespace milk {
	namespace clientbound {
		namespace play {

			struct Login {
				static constexpr ConnectionState connectionState = ConnectionState::Configuration;
				static constexpr int32_t packetId = 0x2B;

				int32_t entityId;
				bool isHardcore;
				std::vector<Identifier> dimensionNames;
				int32_t maxPlayers;
				int32_t viewDistance;
				int32_t simulationDistance;
				bool reducedDebugInfo;
				bool enableRespawnScreen;
				bool doLimitedCrafting;
				int32_t dimensionType;
				Identifier dimensionName;
				int64_t hashedSeed;
				GameMode gameMode;
				GameMode previousGameMode;
				bool isDebug;
				bool isFlat;
				bool hasDeathLocation;
				Identifier deathDimensionName;
				glm::ivec3 deathLocation;
				int32_t portalCooldown;
				bool enforcesSecureChat;

				Packet serialize() const {
					Packet packet;
					packet.writeVarInt(packetId);

					packet.writeInt(entityId);
					packet.writeBool(isHardcore);
					packet.writeVarInt(int32_t(dimensionNames.size()));
					for (const auto& dimension : dimensionNames)
						packet.writeIdentifier(dimension);
					packet.writeVarInt(maxPlayers);
					packet.writeVarInt(viewDistance);
					packet.writeVarInt(simulationDistance);
					packet.writeBool(reducedDebugInfo);
					packet.writeBool(enableRespawnScreen);
					packet.writeBool(doLimitedCrafting);
					packet.writeVarInt(dimensionType);
					packet.writeIdentifier(dimensionName);
					packet.writeLong(hashedSeed);
					packet.writeUByte(uint8_t(gameMode));
					packet.writeByte(int8_t(previousGameMode));
					packet.writeBool(isDebug);
					packet.writeBool(isFlat);
					packet.writeBool(hasDeathLocation);
					if (hasDeathLocation) {
						// todo: position
					}
					packet.writeVarInt(portalCooldown);
					packet.writeBool(enforcesSecureChat);

					return packet;
				}
			};

		}
	}
}