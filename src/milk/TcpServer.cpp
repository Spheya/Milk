#include "TcpServer.hpp"

namespace milk {
	TcpServer::TcpServer(uint16_t port) :
		m_tcpAcceptor(make_strand(m_asioContext), asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)),
		m_packetBus(std::make_shared<EventBus>()) {
	}

	TcpServer::~TcpServer() {
		stop();
	}

	EventBus& TcpServer::getPacketBus() {
		return *m_packetBus;
	}

	const EventBus& TcpServer::getPacketBus() const {
		return *m_packetBus;
	}

	void TcpServer::stop() {
		m_asioContext.stop();
	}

	void TcpServer::run() {
		waitForConnection();
		m_asioContext.run();
	}

	void TcpServer::pollEvents() {
		m_packetBus->executeEventQueue();
	}

	void TcpServer::waitForConnection() {
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
}