#pragma once
#include "scene/BaseScene.h"
#include "Core/types.h"

#include "OpenGl/Camera.h"
#include "OpenGl/QuadBatcher.h"

#include "GameObject/Ball.h"
#include "GameObject/Paddle.h"
#include "GameObject/Block.h"
namespace Game {

	class GameScene : public BaseScene {
		static constexpr auto levelPath = "Assets/level.blocks";
		static constexpr auto blocksTexturePath = "Assets/Textures/Block.png";

		static constexpr auto blocksVertexShader = "Assets/Shaders/DefaultShader.vert";
		static constexpr auto blocksFragmentShader = "Assets/Shaders/DefaultShader.frag";
		static constexpr auto ballVertexShader = "Assets/Shaders/BallShader.vert";
		static constexpr auto ballfragmentShader = "Assets/Shaders/BallShader.frag";

	public: 
		GameScene(Physics::PhysicsManager& p_manager, Renderer::Input::InputManager& i_manager);
		void Update(float deltaTime);
		void Draw();
	private: 
		void InitializeCamera();
		void InitializeBlocks();
		void InitializePaddle();
		void InitializeBall();
	private: 
		// Type definitions
		using VerticeTy = Renderer::Geometry::Point2D;
		using UVTy = Renderer::Geometry::UVCoordinates;
		using ColorTy = Renderer::Type::RawColor;
		using QuadBatcher = Renderer::GL::QuadBatcher<VerticeTy, UVTy, ColorTy>;
	private:
		Renderer::GL::OrthoCamera camera{ SCR_WIDTH,SCR_HEIGHT,0.1f,100.f };

		//Game objects
		std::vector<Game::Block> blocks;
		std::unique_ptr<QuadBatcher> quadBatch;
		std::unique_ptr<Game::Ball> ball;
		std::unique_ptr<Game::Paddle> paddle;
	};
}