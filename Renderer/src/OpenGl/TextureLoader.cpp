#define STB_IMAGE_IMPLEMENTATION
#include "OpenGl/stb_image.h"

#include "OpenGl/TextureLoader.h"


std::expected<Renderer::GL::TextureData, std::string> ImageLoader::LoadTexture(std::string_view path)
{
	Renderer::GL::TextureData texture{};
	stbi_set_flip_vertically_on_load(1);
	texture.data = stbi_load(path.data(), &texture.width, &texture.heigth, &texture.numChannels, 0);

	if (!texture.data || texture.width <= 0 || texture.heigth <= 0)
	{
		return std::unexpected<std::string>{"Error loading texture"};
	}

	return texture;
}

void ImageLoader::FreeTexture(Renderer::GL::TextureData& texture)
{
	stbi_image_free(texture.data);
}
