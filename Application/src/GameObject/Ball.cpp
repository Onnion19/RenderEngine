#include "GameObject/Ball.h"
#include "Physics/PhysicsManager.h"


namespace
{



	// QUAD Vertices
	constexpr std::array<Renderer::Geometry::Point2D, 4> QuadVertices{
		vec2 {-0.5f, 0.5f} ,//TL
		vec2{0.5f,0.5f}, //TR
		vec2{0.5f, -0.5f},  //BR
		vec2{-0.5f, -0.5f} //BL
	};
	//Quad Indices
	constexpr std::array<uint8, 6> QuadIndices{
		2,1,0,
		0,3,2
	};
}

namespace Game
{
	Ball::Ball(Physics::PhysicsManager& manager, const Renderer::GL::Program& shaderProgram, const vec3& position, float radius, float speed, const vec3& initialDirection)
		: physicsManager(Renderer::Core::MakeObserver(&manager))
		, program(shaderProgram)
		, collider(Renderer::Geometry::Circle(position, radius))
		, radius(radius)
		, mruObject({ initialDirection, speed })
		, transform({ position, vec3{0.f}, vec3{radius * 2.f, radius * 2.f,1.f} })
		, vbo(OpenGLUtils::Buffer::BufferType::ARRAY)
		, ibo()
	{
		transform.position = position;
		physicsManager->RegisterCollider(collider);
		collider.RegisterOnCollideCallback([this](const vec3& normal) {
			mruObject.direction = glm::reflect(mruObject.direction, normal);
			mruObject.speed *= 1.02f;
			});

		InitializeVAO();
	}

	Ball::~Ball()
	{
		if (!physicsManager)return;
		physicsManager->UnregisterCollider(collider);
	}

	void Ball::Update(float deltaTime)
	{
		mruObject.Apply(deltaTime, transform.position);
		collider.GetShapeAs< Renderer::Geometry::Circle>().center = transform.position;
		physicsManager->SolveCollision(collider);
	}


	void Ball::InitializeVAO()
	{
		using VBOType = decltype(vbo)::bufferTy;
		vao.Bind();
		// Build VBO
		vbo.Bind();
		std::vector<VBOType> vboData;
		vboData.reserve(4);
		std::transform(QuadVertices.begin(), QuadVertices.end(), std::back_inserter(vboData), [](const vec2& vertice) ->  VBOType {return { vertice, Renderer::Type::BLUE }; });
		vbo.Insert(vboData);
		
		// Build IBO
		ibo.Bind();
		ibo.AddIndices(QuadIndices);
		

		//Build VAO
		Renderer::GL::VertexAtributeObject::AttributePointer<VBOType, Renderer::Geometry::Point2D> position{ 0 ,2, OpenGLUtils::Buffer::GLType::FLOAT, false };
		Renderer::GL::VertexAtributeObject::AttributePointer<VBOType, Renderer::Type::RawColor> color{ 1,4, OpenGLUtils::Buffer::GLType::FLOAT, false };
		vao.EnableAndDefineAttributePointer(position);
		vao.EnableAndDefineAttributePointer(color);

		vbo.SendDataGPU(OpenGLUtils::Buffer::BufferUsage::STATIC_DRAW);
		ibo.SendDataGPU(OpenGLUtils::Buffer::BufferUsage::STATIC_DRAW);
		vao.Unbind();
	}
}

