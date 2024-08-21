#pragma once

#include "Connection.hpp"
#include "milk/protocol/Packet.hpp"
#include "milk/core/EventBus.hpp"

namespace milk {
	namespace net {

		class Server {
		public:
			explicit Server(uint16_t port, asio::io_context& context);
			Server(Server&) = delete;
			Server& operator=(Server&) = delete;
			Server(Server&& other) = default;
			Server& operator=(Server&& other) = default;
			~Server();

			EventBus& getPacketBus();
			const EventBus& getPacketBus() const;

			void pollEvents();

		private:
			void waitForConnection();

			asio::ip::tcp::acceptor m_tcpAcceptor;
			std::vector<std::weak_ptr<Connection>> m_connections;
			std::shared_ptr<EventBus> m_packetBus;
		};

	}
}