#include "PacketHandler.hpp"

#include "milk/net/Connection.hpp"
#include "milk/Protocol.hpp"

#include <iostream>

#define MILK_HANDLE_PACKET(x)                                                       \
case x::packetId: {                                                                 \
	x p = x::deserialize(packet);                                                   \
	if(packet.isValid())                                                            \
		packetBus.invoke(IncomingPacketEvent<x>{ std::move(p), std::move(sender)}); \
	else                                                                            \
		sender->disconnect();                                                       \
} break

namespace milk {
	void handleIncomingPacket(std::shared_ptr<net::Connection> sender, Packet& packet, EventBus& packetBus) {
		int32_t packetId = packet.readVarInt();
		if (!packet.isValid())
			return;

		switch (sender->getState()) {
		case ConnectionState::Handshaking:
			switch (packetId) {
				MILK_HANDLE_PACKET(serverbound::Handshake);
				MILK_HANDLE_PACKET(serverbound::LegacyServerPing);
			}
			break;

		case ConnectionState::Status:
			switch (packetId) {
				MILK_HANDLE_PACKET(serverbound::PingRequest);
				MILK_HANDLE_PACKET(serverbound::StatusRequest);
			}
			break;

		case ConnectionState::Login:
			switch (packetId) {
				MILK_HANDLE_PACKET(serverbound::LoginStart);
				MILK_HANDLE_PACKET(serverbound::LoginAcknowledged);
			}
			break;

		case ConnectionState::Configuration:
			switch (packetId) {
				MILK_HANDLE_PACKET(serverbound::AcknowledgeFinishConfiguration);

			default:
				std::cout << "[configuration] packet received with id: " << packetId << std::endl;
			}
			break;

		case ConnectionState::Play:
			switch (packetId) {
			case 0:

			default:
				std::cout << "[play] packet received with id: " << packetId << std::endl;
			}
			break;
		}
	}
}