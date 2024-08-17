#include <milk.hpp>
#include <iostream>

int main() {
	milk::TcpServer server(25565);

	server.getPacketBus().subscribeImmediateHandler<milk::IncomingPacketEvent<milk::serverbound::Handshake>>(
		[](const auto& packet) {
			packet.sender->setState(packet.packet.nextState);
		}
	);

	server.getPacketBus().subscribeAsyncHandler<milk::IncomingPacketEvent<milk::serverbound::PingRequest>>(
		[](const auto& packet) {
			milk::clientbound::PingResponse response;
			response.payload = packet.packet.payload;
			packet.sender->send(response.serialize());
		}
	);

	server.getPacketBus().subscribeAsyncHandler<milk::IncomingPacketEvent<milk::serverbound::StatusRequest>>(
		[](const auto& packet) {
			milk::clientbound::StatusResponse response;
			response.jsonResponse = "{ \"version\": { \"name\": \"Milk 1.21\", \"protocol\": 767 }, \"description\": { \"text\": \"a milk server\" }, \"players\": { \"max\": 10, \"online\": 0, \"sample\": [] }, \"enforcesSecureChat\": false }";
			packet.sender->send(response.serialize());
		}
	);

	server.getPacketBus().subscribe<milk::IncomingPacketEvent<milk::serverbound::LoginStart>>(
		[](const auto& packet) {
			milk::clientbound::LoginSuccess response;
			response.uuid1 = packet.packet.uuid1;
			response.uuid2 = packet.packet.uuid2;
			response.username = packet.packet.name;

			auto p = response.serialize();
			packet.sender->send(p);
		}
	);

	std::thread serverThread([&]() { server.run(); });

	while (true) {
		server.pollEvents();
	}
}