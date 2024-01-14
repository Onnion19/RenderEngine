#pragma once 

#include "OpenGl/Program.h"
#include "OpenGl/Texture.h"
#include "OpenGl/VertexAttributeObject.h"
namespace Game {

	class PostProcessor
	{
	public:
		PostProcessor(unsigned int width, unsigned int height);
		void BeginRender();
		void EndRender();
		void Draw();
		void Update(float deltaTime);

	private: 
		void initRenderData();

	private:
		// render state
		unsigned int MSFBO, FBO; 
		unsigned int RBO; 
		Renderer::GL::VertexAtributeObject vao;

		Renderer::GL::Program postProcessingShader;
		Renderer::GL::Texture texture;
		unsigned int Width, Height;
		bool Confuse, Chaos, Shake;
	};
}