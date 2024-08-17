#pragma once

#include <memory>
#include "Packet.hpp" 
#include "../EventBus.hpp"

namespace milk {
	class TcpConnection;

	template<typename T>
	struct IncomingPacketEvent {
		T packet;
		std::shared_ptr<TcpConnection> sender;
	};

	void handleIncomingPacket(std::shared_ptr<TcpConnection> sender, Packet& packet, EventBus& packetBus);
}