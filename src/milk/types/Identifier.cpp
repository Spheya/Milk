#include "Identifier.hpp"

#include <sstream>

namespace milk {

	Identifier::Identifier(const char* identifier) :
		m_namespace("minecraft") {
		bool hasNamespace = false;

		std::stringstream stream;
		const char* c = identifier;
		while (*c != 0) {
			if (*c == ':') {
				if (hasNamespace) {
					m_valid = false;
					return;
				}

				m_namespace = stream.str();
				stream.str(std::string());

				hasNamespace = true;
			} else {
				if ((*c >= 'a' && *c <= 'z') || (*c >= '0' && *c <= '9') || *c == '.' || *c == '-' || *c == '_' || (*c == '/' && hasNamespace)) {
					stream << *c;
				} else {
					m_valid = false;
					return;
				}
			}
			++c;
		}

		m_value = stream.str();
	}


	Identifier::Identifier(std::string_view identifier) :
		Identifier(identifier.data())
	{}

	Identifier::Identifier(std::string _namespace, std::string value) :
		m_namespace(std::move(_namespace)),
		m_value(std::move(value))
	{}

	bool Identifier::isValid() const noexcept {
		return m_valid;
	}

	void Identifier::setValue(std::string value) noexcept {
		m_value = std::move(value);
	}

	const std::string& Identifier::getValue() const noexcept {
		return m_value;
	}

	std::string& Identifier::getValue() noexcept {
		return m_value;
	}

	void Identifier::setNamespace(std::string _namespace) noexcept {
		m_namespace = std::move(_namespace);
	}

	const std::string& Identifier::getNamespace() const noexcept {
		return m_namespace;
	}

	std::string& Identifier::getNamespace() noexcept {
		return m_namespace;
	}

	std::string Identifier::stringify() const {
		if (!isValid())
			return "milk:invalid";

		std::stringstream stream;
		stream << m_namespace << ":" << m_value;
		return stream.str();
	}

	std::string Identifier::stringifyMinimal() const {
		if (!isValid())
			return "milk:invalid";

		if (m_namespace == "minecraft")
			return m_value;

		std::stringstream stream;
		stream << m_namespace << ":" << m_value;
		return stream.str();
	}

}