#include "PacketHandler.hpp"

#include "TcpConnection.hpp"
#include "Serverbound.hpp"

#define MILK_HANDLE_PACKET(x) case x::packetId: packetBus.invoke(IncomingPacketEvent<x>{x::deserialize(packet), std::move(sender)}); break

namespace milk {
	void handleIncomingPacket(std::shared_ptr<TcpConnection> sender, Packet& packet, EventBus& packetBus) {
		int32_t packetId = packet.readVarInt();
		if (!packet.isValid())
			return;

		switch (sender->getState()) {
		case ConnectionState::HandShaking:
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
			}
			break;

		case ConnectionState::Transfer:
			switch (packetId) {
			case 0x00:
				break;
			}
			break;
		}
	}
}