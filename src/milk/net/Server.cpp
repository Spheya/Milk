#include "Server.hpp"

namespace milk {
	namespace net {

		Server::Server(uint16_t port, asio::io_context& context) :
			m_tcpAcceptor(make_strand(context), asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)),
			m_packetBus(std::make_shared<EventBus>())
		{
			waitForConnection();
		}

		Server::~Server() {
			m_tcpAcceptor.close();
		}

		EventBus& Server::getPacketBus() {
			return *m_packetBus;
		}

		const EventBus& Server::getPacketBus() const {
			return *m_packetBus;
		}

		void Server::pollEvents() {
			m_packetBus->executeEventQueue();
		}

		void Server::waitForConnection() {
			m_tcpAcceptor.async_accept(
				make_strand(m_tcpAcceptor.get_executor()),
				[this](std::error_code ec, asio::ip::tcp::socket socket) {
					if (!ec) {
						auto connection = std::make_shared<Connection>(std::move(socket), m_packetBus);
						connection->start();
						m_connections.emplace_back(std::move(connection));
					}

					waitForConnection();
				}
			);
		}

	}
}