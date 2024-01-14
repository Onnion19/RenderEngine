#include "scene/BlocksBuilder.h"
#include <fstream>
#include <ranges>
namespace {
	void FileGuard(std::ifstream* f)
	{
		f->close();
		delete f;
	}

	struct ColorProvider
	{

		using color = Renderer::Type::ColorRGBA;

		color NextColor()
		{
			i = (i + 1) % 5;
			return colors[i];
		}
	private: 
		std::array<color, 5> colors{
			color{9.f,0.15f, 0.3f,1.f},
			color{1.f,0.f, 1.f,1.f},
			color{1.f,0.23f, 0.6f,1.f},
			color{0.f,0.9f, 0.1f,1.f},
			color{0.12f,0.36f, 0.6f,1.f}
		};
		int i = 0;
	};
}

namespace Game {
	std::expected<std::vector<Block>, std::string> BlockBuilder::BuildBlocks(Physics::PhysicsManager& manager, std::string_view filePath, const vec3& block_size, const vec3& start, const vec3& offset)
	{
		// Open the file to read the scene
		std::unique_ptr < std::ifstream, decltype(&FileGuard)> file{ new std::ifstream(filePath.data()) , &FileGuard };
		if (!file->is_open() || file->fail())
		{
			return std::unexpected<std::string>{ "Could not open the file " };
		}

		std::vector<Block> blocks;
		blocks.reserve(500);

		// Initial transform
		Core::Transform transform{};
		transform.position = start + vec3{ block_size.x / 2.f, - block_size.y / 2.f, 0.f };

		const auto horizontalOffset = vec3{ offset.x + block_size.x, 0.f, 0.f };
		const auto verticalOffset = vec3{ 0.f, -offset.y - block_size.y, 0.f };
		ColorProvider colorProvider;
		while (!file->eof())
		{
			std::string s;
			std::getline(*file, s);

			for (int c : std::views::transform(s, [](const auto& digit) -> int {return static_cast<int>(digit) - '0'; }))
			{
				if (c > 0)
				{
					auto& block = blocks.emplace_back(manager, transform.position, block_size);
					block.SetColor(colorProvider.NextColor());
				}

				transform.position += horizontalOffset;
			}

			transform.position.x = start.x + block_size.x / 2.f;
			transform.position += verticalOffset;

		}

		return blocks;
	}
}
