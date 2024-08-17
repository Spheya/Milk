#pragma once

#include "TcpConnection.hpp"
#include "../packets/Packet.hpp"
#include "../EventBus.hpp"
#include "../packets/PacketHandler.hpp"

namespace milk {
	class TcpServer {
	public:
		TcpServer(uint16_t port) :
			m_tcpAcceptor(make_strand(m_asioContext), asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)),
			m_packetBus(std::make_shared<EventBus>()) {
		}

		TcpServer(TcpServer&) = delete;
		TcpServer& operator=(TcpServer&) = delete;
		TcpServer(TcpServer&& other) = delete;
		TcpServer& operator=(TcpServer&& other) = delete;

		~TcpServer() {
			stop();
		}

		EventBus& getPacketBus() {
			return *m_packetBus;
		}

		const EventBus& getPacketBus() const {
			return *m_packetBus;
		}

		void stop() {
			m_asioContext.stop();
		}

		void run() {
			waitForConnection();
			m_asioContext.run();
		}

		void pollEvents() {
			m_packetBus->executeEventQueue();
		}

	private:
		void waitForConnection() {
			m_tcpAcceptor.async_accept(
				make_strand(m_tcpAcceptor.get_executor()),
				[this](std::error_code ec, asio::ip::tcp::socket socket) {
					if (!ec) {
						auto connection = std::make_shared<TcpConnection>(std::move(socket), m_packetBus);
						connection->start();
						m_connections.emplace_back(std::move(connection));
					}

					waitForConnection();
				}
			);
		}

		asio::io_context m_asioContext;
		asio::ip::tcp::acceptor m_tcpAcceptor;
		std::vector<std::weak_ptr<TcpConnection>> m_connections;
		std::shared_ptr<EventBus> m_packetBus;
	};
}