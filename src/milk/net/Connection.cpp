#include "Connection.hpp"

#include "milk/protocol/PacketHandler.hpp"

namespace milk {
	namespace net {

		Connection::Connection(asio::ip::tcp::socket socket, std::shared_ptr<EventBus> packetBus) :
			m_socket(std::move(socket)),
			m_packetBus(std::move(packetBus)) {
		}

		void Connection::start() {
			readPacket();
		}

		void Connection::disconnect() {
			m_socket.close();
		}

		bool Connection::isConnected() const {
			return m_socket.is_open();
		}

		void Connection::send(Packet packet) {
			auto self = shared_from_this();

			asio::post(m_socket.get_executor(), [this, self, packet]() {
				m_outgoingHeader.clear();
				m_outgoingHeader.writeVarInt(int32_t(packet.size()));

				asio::write(m_socket, asio::buffer(m_outgoingHeader.data(), m_outgoingHeader.size()));
				asio::write(m_socket, asio::buffer(packet.data(), packet.size()));
			});
		}

		ConnectionState Connection::getState() const {
			return m_connectionState;
		}

		void Connection::setState(ConnectionState state) {
			m_connectionState = state;
		}

		void Connection::readPacket() {
			m_incomingPacket.resetPosition();
			m_incomingPacket.resize(5);
			readPacketHeader(0);
		}

		void Connection::readPacketHeader(int byte) {
			auto self = shared_from_this();
			m_socket.async_read_some(asio::buffer(static_cast<uint8_t*>(m_incomingPacket.data()) + byte, 1), [this, self, byte](asio::error_code ec, size_t length) {
				if (ec) {
					disconnect(); // connection error
					return;
				}

				if (bool(*(static_cast<uint8_t*>(m_incomingPacket.data()) + byte) & 0x80u)) {
					readPacketHeader(byte + 1);
				} else {
					readPacketBody();
				}
			});
		}

		void Connection::readPacketBody() {
			auto self = shared_from_this();
			int packetLength = m_incomingPacket.readVarInt();
			if (!m_incomingPacket.isValid()) {
				disconnect(); // invalid packet header
				return;
			}

			m_incomingPacket.resetPosition();
			m_incomingPacket.resize(packetLength);
			m_socket.async_read_some(asio::buffer(m_incomingPacket.data(), packetLength), [this, self](asio::error_code ec, size_t length) {
				if (ec) {
					disconnect(); // connection error
					return;
				}

				handleIncomingPacket(self, m_incomingPacket, *m_packetBus);

				readPacket();
			});
		}

	}
}