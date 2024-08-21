#include "PaintingVariant.hpp"

namespace milk {

	nbt::Tag milk::PaintingVariant::serialize() const {
		return nbt::Tag::Compound({
			nbt::Tag::String("asset_id", assetId),
			nbt::Tag::Int("height", height),
			nbt::Tag::Int("width", width)
		});
	}

}