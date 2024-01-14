#pragma once
#include <expected>
#include "OpenGl/Texture.h"

namespace ImageLoader {

	std::expected<Renderer::GL::TextureData, std::string> LoadTexture(std::string_view path);

	void FreeTexture(Renderer::GL::TextureData& texture);
}