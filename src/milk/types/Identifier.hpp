#pragma once

#include <string>
#include <string_view>

namespace milk {

	class Identifier {
	public:
		Identifier() = default;
		Identifier(const char* identifier);
		Identifier(std::string_view identifier);
		Identifier(std::string _namespace, std::string value);

		bool isValid() const noexcept;

		void setValue(std::string value) noexcept;
		const std::string& getValue() const noexcept;
		std::string& getValue() noexcept;

		void setNamespace(std::string _namespace) noexcept;
		const std::string& getNamespace() const noexcept;
		std::string& getNamespace() noexcept;

		std::string stringify() const;
		std::string stringifyMinimal() const;

	private:
		std::string m_value;
		std::string m_namespace;
		bool m_valid = true;
	};
}

template<>
struct std::hash<milk::Identifier> {
	std::size_t operator()(const milk::Identifier& identifier) const noexcept {
		std::hash<std::string> hasher;
		size_t result = hasher(identifier.getValue());
		result ^= hasher(identifier.getNamespace()) + 0x9e3779b9 + (result << 6) + (result >> 2);
		return result;
	}
};