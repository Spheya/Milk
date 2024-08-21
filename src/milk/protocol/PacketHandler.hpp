#pragma once

#include <memory>

#include "Packet.hpp" 
#include "milk/core/EventBus.hpp"

namespace milk {
	namespace net {
		class Connection;
	}

	template<typename T>
	struct IncomingPacketEvent {
		T packet;
		std::shared_ptr<net::Connection> sender;
	};

	void handleIncomingPacket(std::shared_ptr<net::Connection> sender, Packet& packet, EventBus& packetBus);
}