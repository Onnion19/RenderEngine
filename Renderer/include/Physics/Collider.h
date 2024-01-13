#pragma once

#include "Geometry/BasicShapes.h"
#include <type_traits>
#include <variant>
namespace Physics {


	class Collider {
		using Shape = std::variant<Renderer::Geometry::Rectangle, Renderer::Geometry::Circle>;
	public:
		using CollisionCallback = std::function<void(const vec3&/*Normal*/)>;
		Collider() = default;

		template<typename T>
		Collider(T&& shape) : shape(shape) {}

		template<typename T>
		void UpdateShape(const T& newShape) {
			shape = { newShape };
		}

		const Shape& GetShape()const { return shape; }

		unsigned int GetId() const { return colliderId; }

		void RegisterOnCollideCallback(CollisionCallback&& c) { callbacks.emplace_back(std::move(c)); }

	private:
		void OnCollision(const vec3& normal)
		{
			for (auto& callback : callbacks)
			{
				callback(normal);
			}
		}

		void UnregisterCallbacks()
		{
			callbacks.clear();
		}
	private:
		unsigned int colliderId = 0;
		Shape shape;
		std::vector<CollisionCallback> callbacks;
		friend class PhysicsManager;

	};
}