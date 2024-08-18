#pragma once

#include <memory>

#include "Packet.hpp" 
#include "milk/core/EventBus.hpp"

namespace milk {
	namespace net {
		class TcpConnection;
	}

	template<typename T>
	struct IncomingPacketEvent {
		T packet;
		std::shared_ptr<net::TcpConnection> sender;
	};

	void handleIncomingPacket(std::shared_ptr<net::TcpConnection> sender, Packet& packet, EventBus& packetBus);
}