#pragma once

#include "milk/protocol/ConnectionState.hpp"
#include "milk/protocol/Packet.hpp"

namespace milk {
	namespace clientbound {
		namespace configuration {

			struct PluginMessage {
				static constexpr ConnectionState connectionState = ConnectionState::Configuration;
				static constexpr int32_t packetId = 0x01;

				Identifier channel;
				std::vector<uint8_t> data;

				Packet serialize() {
					Packet packet;
					packet.writeVarInt(packetId);

					packet.writeIdentifier(channel);
					packet.writeData(data.data(), data.size());

					return packet;
				}
			};

		}
	}
}