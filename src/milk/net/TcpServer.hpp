#pragma once

#include "TcpConnection.hpp"
#include "milk/protocol/Packet.hpp"
#include "milk/core/EventBus.hpp"

namespace milk {
	namespace net {

		class TcpServer {
		public:
			explicit TcpServer(uint16_t port);
			TcpServer(TcpServer&) = delete;
			TcpServer& operator=(TcpServer&) = delete;
			TcpServer(TcpServer&& other) = default;
			TcpServer& operator=(TcpServer&& other) = default;
			~TcpServer();

			EventBus& getPacketBus();
			const EventBus& getPacketBus() const;

			void run();
			void stop();

			void pollEvents();

		private:
			void waitForConnection();

			asio::io_context m_asioContext;
			asio::ip::tcp::acceptor m_tcpAcceptor;
			std::vector<std::weak_ptr<TcpConnection>> m_connections;
			std::shared_ptr<EventBus> m_packetBus;
		};

	}
}