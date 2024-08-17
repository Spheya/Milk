#pragma once

#include "Networking.hpp"
#include "Packet.hpp"
#include "EventBus.hpp"
#include "ConnectionState.hpp"

namespace milk {
	class TcpConnection : public std::enable_shared_from_this<TcpConnection> {
	public:
		TcpConnection(asio::ip::tcp::socket socket, std::shared_ptr<EventBus> packetBus);

		void start();
		void close();

		bool isConnected() const;
		void send(Packet packet);

		ConnectionState getState() const;
		void setState(ConnectionState state);

	private:
		void readPacket();
		void readPacketHeader(int byte);
		void readPacketBody();

	private:
		asio::ip::tcp::socket m_socket;
		Packet m_incomingPacket;
		Packet m_outgoingHeader;
		std::shared_ptr<EventBus> m_packetBus;
		std::atomic<ConnectionState> m_connectionState;
	};
}