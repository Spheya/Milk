#pragma once

#include <string>
#include <nbt.hpp>

namespace milk {

	struct WolfVariant {
		std::string wildTexture;
		std::string tameTexture;
		std::string angryTexture;
		std::vector<std::string> biomes;

		nbt::Tag serialize() const;
	};

}