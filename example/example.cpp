#include <milk.hpp>
#include <milk/Protocol.hpp>

#include <iostream>

int main() {
	milk::Server server(25565);
	server.setupVanillaRegistries();
	server.setupDefaultPacketHandlers();

	server.setServerStatusCallback([]() -> milk::ServerStatus {
		milk::ServerStatus status;
		status.description = "milk example server";
		status.maxPlayers = 10;
		return status;
	});

	server.run();
}