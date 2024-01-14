#pragma once
#include "Core/types.h"
#include <string>
namespace Renderer::GL
{
	struct TextureData
	{
		int width;
		int heigth;
		int numChannels;
		unsigned char* data;
	};

	class Texture {
	public:
		Texture(TextureData data);
		~Texture();
		void Bind();
	private:
		GLBufferId textureId;
		TextureData textureData;
	};
}