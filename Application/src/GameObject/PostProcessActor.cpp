#include "GameObject/PostProcessActor.h"

namespace
{
	constexpr auto postProcessVertex = "Assets/Shaders/PostProcess.vert";
	constexpr auto postProcessFragment = "Assets/Shaders/PostProcess.frag";
	Renderer::GL::Program CreatePostProcessProgram()
	{
		// Takes in the camera cause the projection is always constant
		std::filesystem::path vertex{ postProcessVertex };
		std::filesystem::path fragment{ postProcessFragment };
		Renderer::GL::Shader vs(vertex, OpenGLUtils::Shader::Type::VERTEX);
		Renderer::GL::Shader fs(fragment, OpenGLUtils::Shader::Type::FRAGMENT);
		Renderer::GL::Program program{ vs, fs };

		return program;
	}
}

namespace Game {

	PostProcessor::PostProcessor(unsigned int width, unsigned int height)
		: postProcessingShader(CreatePostProcessProgram()), texture(Renderer::GL::TextureData{ static_cast<int>(width), static_cast<int>(height), 3, nullptr }), Width(width), Height(height), Confuse(false), Chaos(false), Shake(false)
	{
		// initialize renderbuffer/framebuffer object
		glGenFramebuffers(1, &MSFBO);
		glGenFramebuffers(1, &FBO);
		glGenRenderbuffers(1, &RBO);

		// initialize renderbuffer storage with a multisampled color buffer (don't need a depth/stencil buffer)
		glBindFramebuffer(GL_FRAMEBUFFER, MSFBO);
		glBindRenderbuffer(GL_RENDERBUFFER, RBO);
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_RGB, width, height); // allocate storage for render buffer object

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, RBO); // attach MS render buffer object to framebuffer
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::POSTPROCESSOR: Failed to initialize MSFBO" << std::endl;
		// also initialize the FBO/texture to blit multisampled color-buffer to; used for shader operations (for postprocessing effects)
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.Id(), 0); // attach texture to framebuffer as its color attachment
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::POSTPROCESSOR: Failed to initialize FBO" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		// initialize render data and uniforms
		initRenderData();
		postProcessingShader.SetUniform1i("scene", 0);
		float offset = 1.0f / 1920;
		float offsets[9][2] = {
			{ -offset,  offset  },  // top-left
			{  0.0f,    offset  },  // top-center
			{  offset,  offset  },  // top-right
			{ -offset,  0.0f    },  // center-left
			{  0.0f,    0.0f    },  // center-center
			{  offset,  0.0f    },  // center - right
			{ -offset, -offset  },  // bottom-left
			{  0.0f,   -offset  },  // bottom-center
			{  offset, -offset  }   // bottom-right    
		};
		glUniform2fv(glGetUniformLocation(postProcessingShader.GetId(), "offsets"), 9, (float*)offsets);
		int edge_kernel[9] = {
			-1, -1, -1,
			-1,  8, -1,
			-1, -1, -1
		};
		glUniform1iv(glGetUniformLocation(postProcessingShader.GetId(), "edge_kernel"), 9, edge_kernel);
		float blur_kernel[9] = {
			1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f,
			2.0f / 16.0f, 4.0f / 16.0f, 2.0f / 16.0f,
			1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f
		};
		glUniform1fv(glGetUniformLocation(postProcessingShader.GetId() , "blur_kernel"), 9, blur_kernel);
	}

	void PostProcessor::BeginRender()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, MSFBO);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void PostProcessor::EndRender()
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, MSFBO);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBO);
		glBlitFramebuffer(0, 0, Width, Height, 0, 0, Width, Height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void PostProcessor::Update(float deltaTime)
	{
		postProcessingShader.SetUniform1("time", deltaTime);
		postProcessingShader.SetUniform1i("confuse", 0);
		postProcessingShader.SetUniform1i("chaos", 0);
		postProcessingShader.SetUniform1i("shake", 1);
	}

	void PostProcessor::Draw()
	{
		// set uniforms/options
		postProcessingShader.UseProgram();
		texture.Bind();
		vao.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		vao.Unbind();
	}

	void PostProcessor::initRenderData()
	{
		// configure VAO/VBO
		unsigned int VBO;
		float vertices[] = {
			// pos        // tex
			-1.0f, -1.0f, 0.0f, 0.0f,
			 1.0f,  1.0f, 1.0f, 1.0f,
			-1.0f,  1.0f, 0.0f, 1.0f,

			-1.0f, -1.0f, 0.0f, 0.0f,
			 1.0f, -1.0f, 1.0f, 0.0f,
			 1.0f,  1.0f, 1.0f, 1.0f
		};
		glGenBuffers(1, &VBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		vao.Bind();
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		vao.Unbind();
	}
}