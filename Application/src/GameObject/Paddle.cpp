#include "GameObject/Paddle.h"
#include "Input/InputManager.h"
#include "Physics/PhysicsManager.h"


namespace Game
{

	Paddle::Paddle(Renderer::Input::InputManager& inputManager, Physics::PhysicsManager& physicsManager, const vec3& position, float length, float speed)
		: transform({ position, vec3{},vec3{length, 15.f, 1.f}})
		, renderer(transform)
		, collider(Renderer::Geometry::Rectangle(transform))
		, movementData({ vec3{}, speed })
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

	void Paddle::update(float deltatime)
	{
		movementData.Apply(deltatime, transform.position);
		transform.position.x = std::clamp(transform.position.x, 0.f, 1920.f - transform.size.x / 2.f);
		collider.UpdateShape(Renderer::Geometry::Rectangle(transform));
	}

}
