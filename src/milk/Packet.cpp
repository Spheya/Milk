#include "Packet.hpp"

#include <type_traits>
#include <bit>

namespace milk {
	void Packet::invalidate() noexcept {
		m_valid = false;
	}

	bool Packet::isValid() const noexcept {
		return m_valid;
	}

	uint8_t Packet::operator[](size_t index) noexcept {
		return m_data[index];
	}

	Packet::iterator Packet::begin() noexcept {
		return m_data.begin();
	}

	Packet::iterator Packet::end() noexcept {
		return m_data.end();
	}

	Packet::const_iterator Packet::begin() const noexcept {
		return m_data.begin();
	}

	Packet::const_iterator Packet::end() const noexcept {
		return m_data.end();
	}

	const void* Packet::data() const noexcept {
		return m_data.data();
	}

	void* Packet::data() noexcept {
		return m_data.data();
	}

	size_t Packet::size() const noexcept {
		return m_data.size();
	}

	void Packet::writeData(const void* data, size_t size) {
		if (!isValid())
			return;

		size_t offset = m_data.size();
		m_data.resize(m_data.size() + size);
		memcpy(m_data.data() + offset, data, size);
	}

	void Packet::peekData(void* data, size_t size) const {
		if (!isValid() || m_caret + size > m_data.size())
			return;

		memcpy(data, m_data.data() + m_caret, size);
	}

	void Packet::readData(void* data, size_t size) {
		if (!isValid())
			return;
		
		if (m_caret + size > m_data.size()) {
			invalidate();
			return;
		}

		memcpy(data, m_data.data() + m_caret, size);
		m_caret += size;
	}

	void Packet::writeBool(bool value) {
		writeUByte(value ? 0x01 : 0x00);
	}

	bool Packet::peekBool() const {
		return bool(peekUByte());
	}

	bool Packet::readBool() {
		return bool(readUByte());
	}

	void Packet::writeByte(int8_t value) {
		writeUByte(std::bit_cast<uint8_t>(value));
	}

	int8_t Packet::peekByte() const {
		return std::bit_cast<int8_t>(peekUByte());
	}

	int8_t Packet::readByte() {
		return std::bit_cast<int8_t>(readUByte());
	}

	void Packet::writeUByte(uint8_t value) {
		if (!isValid())
			return;

		m_data.push_back(value);
	}

	uint8_t Packet::peekUByte() const {
		if (!isValid() || m_caret >= m_data.size())
			return 0;

		return m_data[m_caret];
	}

	uint8_t Packet::readUByte() {
		if (!isValid())
			return 0;

		if (m_caret + 1 > m_data.size()) {
			invalidate();
			return 0;
		}

		return m_data[m_caret++];
	}

	void Packet::writeShort(int16_t value) {
		writeNumberData(&value, sizeof(int16_t));
	}

	int16_t Packet::peekShort() const {
		int16_t value = 0;
		peekNumberData(&value, sizeof(int16_t));
		return value;
	}

	int16_t Packet::readShort() {
		int16_t value = 0;
		readNumberData(&value, sizeof(int16_t));
		return value;
	}

	void Packet::writeUShort(uint16_t value) {
		writeNumberData(&value, sizeof(uint16_t));
	}

	uint16_t Packet::peekUShort() const {
		uint16_t value = 0;
		peekNumberData(&value, sizeof(uint16_t));
		return value;
	}

	uint16_t Packet::readUShort() {
		uint16_t value = 0;
		readNumberData(&value, sizeof(uint16_t));
		return value;
	}

	void Packet::writeInt(int32_t value) {
		writeNumberData(&value, sizeof(int32_t));
	}

	int32_t Packet::peekInt() const {
		int32_t value = 0;
		peekNumberData(&value, sizeof(int32_t));
		return value;
	}

	int32_t Packet::readInt() {
		int32_t value = 0;
		readNumberData(&value, sizeof(int32_t));
		return value;
	}

	void Packet::writeLong(int64_t value) {
		writeNumberData(&value, sizeof(int64_t));
	}

	int64_t Packet::peekLong() const {
		int64_t value = 0;
		peekNumberData(&value, sizeof(int64_t));
		return value;
	}

	int64_t Packet::readLong() {
		int64_t value = 0;
		readNumberData(&value, sizeof(int64_t));
		return value;
	}

	void Packet::writeFloat(float value) {
		// todo: this assumes that the system uses IEEE 754 floating point numbers, maybe not assume that
		writeInt(std::bit_cast<int32_t>(value));
	}

	float Packet::peekFloat() const {
		// todo: this assumes that the system uses IEEE 754 floating point numbers, maybe not assume that
		return std::bit_cast<float>(peekInt());
	}

	float Packet::readFloat() {
		// todo: this assumes that the system uses IEEE 754 floating point numbers, maybe not assume that
		return std::bit_cast<float>(readInt());
	}

	void Packet::writeDouble(double value) {
		// todo: this assumes that the system uses IEEE 754 floating point numbers, maybe not assume that
		writeLong(std::bit_cast<int64_t>(value));
	}

	double Packet::peekDouble() const {
		// todo: this assumes that the system uses IEEE 754 floating point numbers, maybe not assume that
		return std::bit_cast<double>(peekLong());
	}

	double Packet::readDouble() {
		// todo: this assumes that the system uses IEEE 754 floating point numbers, maybe not assume that
		return std::bit_cast<double>(readLong());
	}

	void Packet::writeString(const std::string& value) {
		writeVarInt(value.size());
		writeData(value.data(), value.size());
	}

	std::string Packet::peekString() const {
		size_t offset = 0;
		int32_t size = peekVarInt(offset);

		if (!isValid() || m_caret + size + offset > m_data.size())
			return "";

		std::string str(static_cast<const char*>(data()) + m_caret + offset, size);
		return str;
	}

	std::string Packet::readString() {
		int32_t size = readVarInt();

		if (!isValid())
			return "";

		if (m_caret + size > m_data.size()) {
			invalidate();
			return "";
		}

		std::string str(static_cast<const char*>(data()) + m_caret, size);
		m_caret += size;
		return str;
	}

	void Packet::writeNumberData(const void* data, size_t size) {
		writeData(data, size);

		if constexpr (std::endian::native == std::endian::little) {
			if (!isValid())
				return;

			std::reverse(m_data.begin() + m_data.size() - size, m_data.begin() + m_data.size());
		}
	}

	void Packet::peekNumberData(void* data, size_t size) const {
		peekData(data, size);
		
		if constexpr (std::endian::native == std::endian::little) {
			if (!isValid())
				return;
			
			std::reverse(static_cast<uint8_t*>(data), static_cast<uint8_t*>(data) + size);
		}
	}

	void Packet::readNumberData(void* data, size_t size) {
		readData(data, size);

		if constexpr (std::endian::native == std::endian::little) {
			if (!isValid())
				return;

			std::reverse(static_cast<uint8_t*>(data), static_cast<uint8_t*>(data) + size);
		}
	}

	void Packet::writeVarInt(int32_t value) {
		if (!isValid())
			return;

		uint32_t uValue = std::bit_cast<uint32_t>(value);
		
		while (true) {
			if ((uValue & ~0x7Fu) == 0) {
				m_data.push_back(uValue);
				return;
			}

			m_data.push_back((uValue & 0x7Fu) | 0x80u);
			uValue >>= 7;
		}
	}

	int32_t Packet::peekVarInt() const {
		size_t size = 0;
		return peekVarInt(size);
	}

	int32_t Packet::peekVarInt(size_t& size) const {
		if (!isValid())
			return 0;

		size = 0;
		size_t caret = m_caret;
		uint32_t value = 0;
		int position = 0;
		uint8_t currentByte;

		while (true) {
			if (caret > m_data.size())
				return 0;

			currentByte = m_data[caret++];
			value |= uint32_t(currentByte & 0x7Fu) << position;

			if ((currentByte & 0x80u) == 0) break;

			position += 7;

			if (position > 32) return 0;
		}

		size = caret - m_caret;
		return std::bit_cast<int32_t>(value);
	}

	int32_t Packet::readVarInt() {
		if (!isValid())
			return 0;

		size_t caret = m_caret;
		uint32_t value = 0;
		int position = 0;
		uint8_t currentByte;

		while (true) {
			if (caret > m_data.size()) {
				invalidate();
				return 0;
			}

			currentByte = m_data[caret++];
			value |= uint32_t(currentByte & 0x7Fu) << position;

			if ((currentByte & 0x80u) == 0) break;

			position += 7;

			if (position > 32) {
				invalidate();
				return 0;
			}
		}

		m_caret = caret;
		return std::bit_cast<int32_t>(value);
	}

	void Packet::writeVarLong(int64_t value) {
		if (!isValid())
			return;

		uint64_t uValue = std::bit_cast<uint64_t>(value);

		while (true) {
			if ((uValue & ~0x7Fu) == 0) {
				m_data.push_back(uValue);
				return;
			}

			m_data.push_back((uValue & 0x7Fu) | 0x80u);
			uValue >>= 7;
		}
	}

	int64_t Packet::peekVarLong() const {
		size_t size = 0;
		return peekVarLong(size);
	}

	int64_t Packet::peekVarLong(size_t& size) const {
		if (!isValid())
			return 0;

		size = 0;
		size_t caret = m_caret;
		uint64_t value = 0;
		int position = 0;
		uint8_t currentByte;

		while (true) {
			if (caret > m_data.size())
				return 0;

			currentByte = m_data[caret++];
			value |= uint64_t(currentByte & 0x7Fu) << position;

			if ((currentByte & 0x80u) == 0) break;

			position += 7;

			if (position > 32) return 0;
		}

		size = caret - m_caret;
		return std::bit_cast<int64_t>(value);
	}

	int64_t Packet::readVarLong() {
		if (!isValid())
			return 0;

		size_t caret = m_caret;
		uint64_t value = 0;
		int position = 0;
		uint8_t currentByte;

		while (true) {
			if (caret > m_data.size()) {
				invalidate();
				return 0;
			}

			currentByte = m_data[caret++];
			value |= uint64_t(currentByte & 0x7Fu) << position;

			if ((currentByte & 0x80u) == 0) break;

			position += 7;

			if (position > 32) {
				invalidate();
				return 0;
			}
		}

		m_caret = caret;
		return std::bit_cast<int64_t>(value);
	}

}