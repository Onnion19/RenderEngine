#pragma once

#include "GameObject/Block.h"
#include <string_view>
#include <expected>

namespace Physics {
	class PhysicsManager;
}

namespace Game {
	class BlockBuilder {
	public:
		static std::expected<std::vector<Block>, std::string> BuildBlocks(Physics::PhysicsManager& manager, std::string_view filePath, const vec3& block_size, const vec3& start, const vec3& offset);
	};

}