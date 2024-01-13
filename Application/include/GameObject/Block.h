#pragma once

#include "OpenGl/Quad.h"
#include "Physics/Collider.h"

namespace Physics {
	class PhysicsManager;
}

namespace Game {

	class Block {	
		inline static const vec3 defaultSize = vec3{ 20.f, 20.f, 1.f };
	public: 
		using Color = Renderer::Type::ColorRGBA;
		Block() = default;
		Block(Physics::PhysicsManager& manager, const vec3 position, const vec3& size = defaultSize);

		void SetColor(const Color& color);
		const Color& GetColor()const;

		void RegisterOnCollideCallback(Physics::Collider::CollisionCallback&& callback);
		auto getVBOData() const { return quad.GetVBOData(); }
		
		void SetId(uint32 id);
		uint32 GetId()const;
	private:
		Renderer::GL::BasicQuad quad;
		uint32 quadID = 0;

		Physics::Collider collider;

	};
}