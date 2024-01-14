#include "scene/GameScene.h"
#include "Core/Settings.h"
#include "scene/BlocksBuilder.h"


namespace {
	Renderer::GL::Program CreateBatchProgram(auto& camera)
	{
		// Takes in the camera cause the projection is always constant
		std::filesystem::path vertex{ "Assets/Shaders/DefaultShader.vert" };
		std::filesystem::path fragment{ "Assets/Shaders/DefaultShader.frag" };
		Renderer::GL::Shader vs(vertex, OpenGLUtils::Shader::Type::VERTEX);
		Renderer::GL::Shader fs(fragment, OpenGLUtils::Shader::Type::FRAGMENT);
		Renderer::GL::Program program{ vs, fs };
		//program.SetUniform1i("ourTexture", 0);
		program.SetUniformMatrix4("model", glm::identity<mat4>());
		program.SetUniformMatrix4("view", camera.GetViewMatrix());
		program.SetUniformMatrix4("projection", camera.GetProjectionMatrix());

		return program;
	}


	Renderer::GL::Program CreateBallProgram(auto& camera)
	{
		// Takes in the camera cause the projection is always constant
		std::filesystem::path vertex{ "Assets/Shaders/BallShader.vert" };
		std::filesystem::path fragment{ "Assets/Shaders/BallShader.frag" };
		Renderer::GL::Shader vs(vertex, OpenGLUtils::Shader::Type::VERTEX);
		Renderer::GL::Shader fs(fragment, OpenGLUtils::Shader::Type::FRAGMENT);
		Renderer::GL::Program program{ vs, fs };
		program.SetUniformMatrix4("model", glm::identity<mat4>());
		program.SetUniformMatrix4("view", camera.GetViewMatrix());
		program.SetUniformMatrix4("projection", camera.GetProjectionMatrix());

		return program;
	}
}

namespace Game {

	GameScene::GameScene(Physics::PhysicsManager& p_manager, Renderer::Input::InputManager& i_manager)
		: BaseScene(p_manager, i_manager)
	{
		InitializeCamera();
		InitializeBlocks();
		InitializeBall();
		InitializePaddle();
	}

	void GameScene::Update(float deltaTime)
	{
		paddle->update(deltaTime);
		ball->Update(deltaTime);
	}
	void GameScene::Draw()
	{
		quadBatch->Draw();
		paddle->Draw();
		ball->Draw();
	}
	void GameScene::InitializeCamera()
	{
		camera.Translate(vec3{ 0.f,0.f,-10.f });
	}

	void GameScene::InitializeBlocks()
	{
		// Load required textures
		auto blockTexture = ImageLoader::LoadTexture("Assets/Textures/Block.png");
		RenderAssert(blockTexture, blockTexture.error().c_str());

		// Load blocks information from level file
		auto generatedBlocks = Game::BlockBuilder::BuildBlocks(*physicsManager, "Assets/level.blocks", vec3{170.f, 50.f, 0.f}, vec3{90.f, SCR_HEIGHT * 0.9f, -1.f}, vec3{10.f, 10.f, 0.f});
		RenderAssert(generatedBlocks, generatedBlocks.error().c_str());

		blocks = std::move(generatedBlocks.value());

		auto defaultProgram = CreateBatchProgram(camera);

		// Add blocks to batcher tool
		quadBatch = std::make_unique< QuadBatcher>( defaultProgram, blockTexture.value() );
		for (auto& block : blocks)
		{
			// Add the quads to batch
			auto id = quadBatch->AddQuad(block.getVBOData());
			//Add collision hit callback
			block.RegisterOnCollideCallback([batch = quadBatch.get(), id](const vec3&) {batch->HideQuad(id); });
		}
		// Finish to setup batching
		quadBatch->SendQuadDataToGPU();

	}

	void GameScene::InitializePaddle()
	{
		paddle = std::make_unique<Game::Paddle>(*inputmanager, *physicsManager, camera, vec3{ SCR_WIDTH / 2.f, 15.f, -1.f }, 340.f, 560.f);
	}

	void GameScene::InitializeBall()
	{
		ball = std::make_unique<Game::Ball>(*physicsManager, CreateBallProgram(camera), vec3{ 500.f,500.f, -1.f }, 30.f, 280.f, glm::normalize(vec3{ 0.1f, +0.9f,0.f }));
	}
}
