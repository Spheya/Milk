#include "WolfVariant.hpp"

namespace milk {

	nbt::Tag milk::WolfVariant::serialize() const {
		nbt::Tag tag =  nbt::Tag::Compound({
			nbt::Tag::String("wild_texture", wildTexture),
			nbt::Tag::String("tame_texture", tameTexture),
			nbt::Tag::String("angry_texture", angryTexture)
		});

		if (biomes.size() == 1) {
			tag.addChild(nbt::Tag::String("biomes", biomes[0]));
		} else {
			nbt::Tag biomeList = nbt::Tag::List("biomes", {});
			for (const auto& biome : biomes) {
				biomeList.addChild(nbt::Tag::String(biome));
			}
			tag.addChild(std::move(biomeList));
		}

		return tag;
	}

}