#pragma once

#include <string>
#include <nbt.hpp>

namespace milk {

	struct PaintingVariant {
		std::string assetId;
		int height;
		int width;

		nbt::Tag serialize() const;
	};

}