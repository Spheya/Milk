#include "DimensionType.hpp"

nbt::Tag milk::DimensionType::serialize() const {
	auto tag = nbt::Tag::Compound({
		nbt::Tag::Byte("has_skylight", int8_t(hasSkylight)),
		nbt::Tag::Byte("has_ceiling", int8_t(hasCeiling)),
		nbt::Tag::Byte("ultrawarm", int8_t(ultrawarm)),
		nbt::Tag::Byte("natural", int8_t(natural)),
		nbt::Tag::Double("coordinate_scale", double(coordinateScale)),
		nbt::Tag::Byte("bed_works", int8_t(bedWorks)),
		nbt::Tag::Byte("respawn_anchor_works", int8_t(respawnAnchorWorks)),
		nbt::Tag::Int("min_y", minY),
		nbt::Tag::Int("height", height),
		nbt::Tag::Int("logical_height", logicalHeight),
		nbt::Tag::String("infiniburn", infiniburn),
		nbt::Tag::String("effects", effects),
		nbt::Tag::Float("ambient_light", ambientLight),
		nbt::Tag::Byte("piglin_safe", int8_t(piglinSafe)),
		nbt::Tag::Byte("has_raids", int8_t(hasRaids)),
		nbt::Tag::Int("monster_spawn_light_level", monsterSpawnLightLevel),
		nbt::Tag::Int("monster_spawn_block_light_limit", monsterSpawnBlockLightLimit),
		
	});

	if(hasFixedTime)
		tag.addChild(nbt::Tag::Long("fixed_time", fixedTime));

	return tag;
}
