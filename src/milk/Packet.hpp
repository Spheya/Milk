#pragma once

#include <vector>
#include <string>

namespace milk {

	class Packet {
	public:
		using iterator = std::vector<uint8_t>::iterator;
		using const_iterator = std::vector<uint8_t>::const_iterator;

	public:
		void invalidate() noexcept;
		bool isValid() const noexcept;

		uint8_t operator[](size_t index) noexcept;
		iterator begin() noexcept;
		iterator end() noexcept;
		const_iterator begin() const noexcept;
		const_iterator end() const noexcept;

		const void* data() const noexcept;
		void* data() noexcept;
		size_t size() const noexcept;

		void writeData(const void* data, size_t size);
		void peekData(void* data, size_t size) const;
		void readData(void* data, size_t size);

		void writeBool(bool value);
		bool peekBool() const;
		bool readBool();

		void writeByte(int8_t value);
		int8_t peekByte() const;
		int8_t readByte();

		void writeUByte(uint8_t value);
		uint8_t peekUByte() const;
		uint8_t readUByte();

		void writeShort(int16_t value);
		int16_t peekShort() const;
		int16_t readShort();

		void writeUShort(uint16_t value);
		uint16_t peekUShort() const;
		uint16_t readUShort();

		void writeInt(int32_t value);
		int32_t peekInt() const;
		int32_t readInt();

		void writeLong(int64_t value);
		int64_t peekLong() const;
		int64_t readLong();

		void writeFloat(float value);
		float peekFloat() const;
		float readFloat();

		void writeDouble(double value);
		double peekDouble() const;
		double readDouble();

		void writeString(const std::string& value);
		std::string peekString() const;
		std::string readString();

		void writeVarInt(int32_t value);
		int32_t peekVarInt() const;
		int32_t peekVarInt(size_t& size) const;
		int32_t readVarInt();

		void writeVarLong(int64_t value);
		int64_t peekVarLong() const;
		int64_t peekVarLong(size_t& size) const;
		int64_t readVarLong();

	private:
		/**
		 * @brief Same as writeData, but keeps endianness in mind
		 * @param data The data to write to the packet
		 * @param size The size of the data array in bytes
		 */
		void writeNumberData(const void* data, size_t size);

		/**
		 * @brief Same as peekData, but keeps endianness in mind
		 * @param data The memory to write the data to
		 * @param size How far to peek into the packet
		 */
		void peekNumberData(void* data, size_t size) const;

		/**
		 * @brief Same as readData, but keeps endianness in mind
		 * @param data The memory to write the data to
		 * @param size How far to read into the packet
		 */
		void readNumberData(void* data, size_t size);

	private:
		std::vector<uint8_t> m_data;
		size_t m_caret = 0;
		bool m_valid = true;
	};

}