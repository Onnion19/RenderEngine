#include "scene/BlocksBuilder.h"
#include <fstream>
#include <ranges>

namespace {
	void FileGuard(std::ifstream* f)
	{
		f->close();
		delete f;
	}
}

namespace Game {
	std::expected<std::vector<Block>, std::string> BlockBuilder::BuildBlocks(std::string_view filePath, const vec3& block_size, const vec3& start, const vec3& offset)
	{
		// Open the file to read the scene
		std::unique_ptr < std::ifstream, decltype(&FileGuard)> file{ new std::ifstream(filePath.data()) , &FileGuard };
		if (!file->is_open() || file->fail())
		{
			return std::unexpected<std::string>{ "Could not open the file " };
		}

		std::vector<Block> blocks;
		blocks.reserve(50);

		// Initial transform
		Core::Transform transform{};
		transform.position = start;

		const auto horizontalOffset = vec3{ offset.x + block_size.x, 0.f, 0.f };
		const auto verticalOffset = vec3{ 0.f, -offset.y - block_size.y, 0.f };

		while (!file->eof())
		{
			std::string s;
			std::getline(*file, s);

			for (int c : std::views::transform(s, [](const auto& digit) -> int {return static_cast<int>(digit) - '0'; }))
			{
				if (c > 0)
				{
					blocks.emplace_back(transform.position, block_size);
				}

				transform.position += horizontalOffset;
			}

			transform.position.x = start.x;
			transform.position += verticalOffset;

		}

		return blocks;
	}
}
