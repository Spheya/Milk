#pragma once

#include <nbt.hpp>

#include "milk/types/Identifier.hpp"

namespace milk {

	template<typename T>
	class Registry {
	public:
		class Entry {
			friend class Registry<T>;
		public:
			Entry(milk::Identifier identifier, const T& value);
			const milk::Identifier& getIdentifier() const noexcept;
			const T& getValue() const noexcept;
			const nbt::Data& getNbtData() const noexcept;

		private:
			milk::Identifier m_identifier;
			T m_value;
			nbt::Data m_nbtData;
			size_t m_hash;
		};

	public:
		explicit Registry(milk::Identifier identifier);

		const milk::Identifier& getIdentifier() const noexcept;

		size_t entryCount() const noexcept;
		const Entry& getEntry(size_t idx) const noexcept;
		const Entry* getEntry(const milk::Identifier& identifier) const noexcept;
		size_t getEntryIndex(const milk::Identifier& identifier) const noexcept;
		
		void add(milk::Identifier identifier, const T& value);

	private:
		milk::Identifier m_identifier;
		std::vector<Entry> m_entries;
	};

	template<typename T>
	inline Registry<T>::Entry::Entry(milk::Identifier identifier, const T& value) :
		m_identifier(std::move(identifier)),
		m_value(value),
		m_nbtData(m_value.serialize().serialize(nbt::SerializationFlag::JavaNetwork)),
		m_hash(std::hash<milk::Identifier>()(m_identifier))
	{}

	template<typename T>
	inline const milk::Identifier& Registry<T>::Entry::getIdentifier() const noexcept {
		return m_identifier;
	}

	template<typename T>
	inline const T& Registry<T>::Entry::getValue() const noexcept {
		return m_value;
	}

	template<typename T>
	inline const nbt::Data& Registry<T>::Entry::getNbtData() const noexcept {
		return m_nbtData;
	}

	template<typename T>
	inline Registry<T>::Registry(milk::Identifier identifier) :
		m_identifier(identifier)
	{}

	template<typename T>
	inline const milk::Identifier& Registry<T>::getIdentifier() const noexcept {
		return m_identifier;
	}

	template<typename T>
	inline size_t Registry<T>::entryCount() const noexcept {
		return m_entries.size();
	}

	template<typename T>
	inline const Registry<T>::Entry& Registry<T>::getEntry(size_t idx) const noexcept {
		return m_entries[idx];
	}

	template<typename T>
	inline const Registry<T>::Entry* Registry<T>::getEntry(const milk::Identifier& identifier) const noexcept {
		size_t hash = std::hash<milk::Identifier>()(identifier);
		
		for (auto& entry : m_entries)
			if (entry.m_hash == hash)
				return &entry;

		return nullptr;
	}

	template<typename T>
	inline size_t Registry<T>::getEntryIndex(const milk::Identifier& identifier) const noexcept {
		size_t hash = std::hash<milk::Identifier>()(identifier);

		for (size_t i = 0; i < m_entries.size(); ++i)
			if (m_entries[i].m_hash == hash)
				return i;

		return 0;
	}

	template<typename T>
	inline void Registry<T>::add(milk::Identifier identifier, const T& value) {
		m_entries.emplace_back(std::move(identifier), value);
	}

}