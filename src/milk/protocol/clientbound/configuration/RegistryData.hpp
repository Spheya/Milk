#pragma once

#include "milk/protocol/ConnectionState.hpp"
#include "milk/protocol/Packet.hpp"
#include "milk/registry/Registry.hpp"

namespace milk {
	namespace clientbound {
		namespace configuration {

			template<typename T>
			struct RegistryData {
				static constexpr ConnectionState connectionState = ConnectionState::Configuration;
				static constexpr int32_t packetId = 0x07;

				Registry<T>* registry;

				Packet serialize() {
					Packet packet;
					packet.writeVarInt(packetId);
					packet.writeIdentifier(registry->getIdentifier());
					packet.writeVarInt(int32_t(registry->entryCount()));
					
					for (size_t i = 0; i < registry->entryCount(); ++i) {
						auto& entry = registry->getEntry(i);
						packet.writeIdentifier(entry.getIdentifier());
						packet.writeBool(true);
						packet.writeNbtData(entry.getNbtData());
					}

					return packet;
				}
			};

		}
	}
}