#include "GameObject/Paddle.h"
#include "Input/InputManager.h"
#include "Physics/PhysicsManager.h"


namespace Game
{
	void Paddle::update(float deltatime)
	{
		movementData.Apply(deltatime, transform.position);
		transform.position.x = std::clamp(transform.position.x, 0.f, 1920.f - transform.size.x / 2.f);
		collider.UpdateShape(Renderer::Geometry::Rectangle(transform));
	}

	void Paddle::Draw()
	{
		renderer.Draw();
	}

	void Paddle::Init(Renderer::Input::InputManager& inputManager, Physics::PhysicsManager& physicsManager)
	{
		physicsManager.RegisterCollider(collider);

		auto moveLeftLambda = [this](const Renderer::Input::KeyInfo&)
			{
				movementData.direction = vec3{ -1.f,0.f,0.f };
			};

		auto moveRightLambda = [this](const Renderer::Input::KeyInfo&)
			{
				movementData.direction = vec3{ 1.f,0.f,0.f };
			};

		auto dontMoveLambda = [this](const Renderer::Input::KeyInfo&)
			{
				movementData.direction = vec3{ 0.f,0.f,0.f };
			};

		inputToken = inputManager.RegisterEvent(std::move(moveLeftLambda), Renderer::Input::KeyboardCode::Z, Renderer::Input::ButtonStatus::DOWN);
		inputManager.RegisterEvent(inputToken, std::move(moveRightLambda), Renderer::Input::KeyboardCode::C, Renderer::Input::ButtonStatus::DOWN);
		inputManager.RegisterEvent(inputToken, dontMoveLambda, Renderer::Input::KeyboardCode::Z, Renderer::Input::ButtonStatus::UP);
		inputManager.RegisterEvent(inputToken, dontMoveLambda, Renderer::Input::KeyboardCode::C, Renderer::Input::ButtonStatus::UP);
	}

}
