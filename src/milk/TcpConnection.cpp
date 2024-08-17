#include "TcpConnection.hpp"

#include "PacketHandler.hpp"

namespace milk {

	TcpConnection::TcpConnection(asio::ip::tcp::socket socket, std::shared_ptr<EventBus> packetBus) :
		m_socket(std::move(socket)),
		m_packetBus(std::move(packetBus)) {
	}

	void TcpConnection::start() {
		readPacket();
	}

	void TcpConnection::close() {
		m_socket.close();

	}

	bool TcpConnection::isConnected() const {
		return m_socket.is_open();
	}

	void TcpConnection::send(Packet packet) {
		auto self = shared_from_this();

		asio::post(m_socket.get_executor(), [this, self, packet]() {
			m_outgoingHeader.clear();
			m_outgoingHeader.writeVarInt(int32_t(packet.size()));

			asio::write(m_socket, asio::buffer(m_outgoingHeader.data(), m_outgoingHeader.size()));
			asio::write(m_socket, asio::buffer(packet.data(), packet.size()));
		});
	}

	ConnectionState TcpConnection::getState() const {
		return m_connectionState;
	}

	void TcpConnection::setState(ConnectionState state) {
		m_connectionState = state;
	}

	void TcpConnection::readPacket() {
		m_incomingPacket.resetPosition();
		m_incomingPacket.resize(5);
		readPacketHeader(0);
	}

	void TcpConnection::readPacketHeader(int byte) {
		auto self = shared_from_this();
		m_socket.async_read_some(asio::buffer(static_cast<uint8_t*>(m_incomingPacket.data()) + byte, 1), [this, self, byte](asio::error_code ec, size_t length) {
			if (ec) {
				close(); // connection error
				return;
			}

			if (bool(*(static_cast<uint8_t*>(m_incomingPacket.data()) + byte) & 0x80u)) {
				readPacketHeader(byte + 1);
			} else {
				readPacketBody();
			}
		});
	}

	void TcpConnection::readPacketBody() {
		auto self = shared_from_this();
		int packetLength = m_incomingPacket.readVarInt();
		if (!m_incomingPacket.isValid()) {
			close(); // invalid packet header
			return;
		}

		m_incomingPacket.resetPosition();
		m_incomingPacket.resize(packetLength);
		m_socket.async_read_some(asio::buffer(m_incomingPacket.data(), packetLength), [this, self](asio::error_code ec, size_t length) {
			if (ec) {
				close(); // connection error
				return;
			}

			handleIncomingPacket(self, m_incomingPacket, *m_packetBus);

			readPacket();
		});
	}
}