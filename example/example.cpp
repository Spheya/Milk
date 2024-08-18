#include <milk.hpp>
#include <iostream>

int main() {
	milk::TcpServer server(25565);

	server.getPacketBus().subscribeImmediateHandler<milk::IncomingPacketEvent<milk::serverbound::Handshake>>(
		[](const milk::IncomingPacketEvent<milk::serverbound::Handshake>& packet) {
			switch (packet.packet.nextState) {
			case milk::serverbound::Handshake::NextState::Status:
				packet.sender->setState(milk::ConnectionState::Status);
				break;

			case milk::serverbound::Handshake::NextState::Login:
				packet.sender->setState(milk::ConnectionState::Login);
				break;

			case milk::serverbound::Handshake::NextState::Transfer:
				packet.sender->setState(milk::ConnectionState::Login);
				break;

			default:
				packet.sender->disconnect();
				break;
			}
		}
	);

	server.getPacketBus().subscribeAsyncHandler<milk::IncomingPacketEvent<milk::serverbound::PingRequest>>(
		[](const milk::IncomingPacketEvent<milk::serverbound::PingRequest>& packet) {
			milk::clientbound::PingResponse response;
			response.payload = packet.packet.payload;
			packet.sender->send(response.serialize());
		}
	);

	server.getPacketBus().subscribe<milk::IncomingPacketEvent<milk::serverbound::StatusRequest>>(
		[](const milk::IncomingPacketEvent<milk::serverbound::StatusRequest>& packet) {
			milk::clientbound::StatusResponse response;
			response.jsonResponse = "{ \"version\": { \"name\": \"Milk 1.21\", \"protocol\": 767 }, \"description\": { \"text\": \"a milk server\" }, \"players\": { \"max\": 10, \"online\": 0, \"sample\": [] }, \"enforcesSecureChat\": false }";
			packet.sender->send(response.serialize());
		}
	);

	server.getPacketBus().subscribe<milk::IncomingPacketEvent<milk::serverbound::LoginStart>>(
		[](const milk::IncomingPacketEvent<milk::serverbound::LoginStart>& packet) {
			milk::clientbound::LoginSuccess response;
			response.uuid = packet.packet.uuid;
			response.username = packet.packet.name;

			packet.sender->send(response.serialize());
		}
	);

	server.getPacketBus().subscribeImmediateHandler<milk::IncomingPacketEvent<milk::serverbound::LoginAcknowledged>>(
		[](const milk::IncomingPacketEvent<milk::serverbound::LoginAcknowledged>& packet) {
			packet.sender->setState(milk::ConnectionState::Configuration);

			milk::clientbound::FinishConfiguration response;
			packet.sender->send(response.serialize());
		}
	);

	server.getPacketBus().subscribeImmediateHandler<milk::IncomingPacketEvent<milk::serverbound::AcknowledgeFinishConfiguration>>(
		[](const milk::IncomingPacketEvent<milk::serverbound::AcknowledgeFinishConfiguration>& packet) {
			packet.sender->setState(milk::ConnectionState::Play);

			milk::clientbound::ChunkBatchStart response1;
			packet.sender->send(response1.serialize());

			milk::clientbound::ChunkBatchFinished response2{0};
			packet.sender->send(response2.serialize());
		}
	);

	std::thread serverThread([&]() { server.run(); });

	while (true) {
		server.pollEvents();
	}
}