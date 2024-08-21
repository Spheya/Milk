#pragma once

#include <cstdint>
#include <string>
#include <nbt.hpp>

namespace milk {

	struct DimensionType {
		bool hasFixedTime;
		int64_t fixedTime;
		bool hasSkylight;
		bool hasCeiling;
		bool ultrawarm;
		bool natural;
		float coordinateScale;
		bool bedWorks;
		bool respawnAnchorWorks;
		int minY;
		int height;
		int logicalHeight;
		std::string infiniburn;
		std::string effects;
		float ambientLight;
		bool piglinSafe;
		bool hasRaids;
		int monsterSpawnLightLevel;
		int monsterSpawnBlockLightLimit;

		nbt::Tag serialize() const;
	};

}