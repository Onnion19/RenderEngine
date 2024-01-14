#include "GameObject/Ball.h"
#include "Physics/PhysicsManager.h"

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
		collider.RegisterOnCollideCallback([this, radius](const vec3& normal) {
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

		if (transform.position.y > 1080.f)
		{
			mruObject.direction = glm::reflect(mruObject.direction, vec3{ 0.f,-1.f, 0.f });
		}
		else if (transform.position.x < radius)
		{
			mruObject.direction = glm::reflect(mruObject.direction, vec3{ 1.f,0.f, 0.f });
		}
		else if (transform.position.x > 1920.f - radius)
		{
			mruObject.direction = glm::reflect(mruObject.direction, vec3{ -1.f,0.f, 0.f });
		}
	}


	void Ball::InitializeVAO()
	{
		using VBOType = decltype(vbo)::bufferTy;
		vao.Bind();
		// Build VBO
		vbo.Bind();
		std::vector<VBOType> vboData;
		vboData.reserve(4);
		std::transform(Renderer::Geometry::NormalQuad::QuadVertices.begin(), Renderer::Geometry::NormalQuad::QuadVertices.end(), std::back_inserter(vboData), [=](const vec2& vertice) ->  VBOType {return { vertice, {transform.position.x, transform.position.y, radius} }; });
		vbo.Insert(vboData);

		// Build IBO
		ibo.Bind();
		ibo.AddIndices(Renderer::Geometry::NormalQuad::QuadIndices);


		//Build VAO
		Renderer::GL::VertexAtributeObject::AttributePointer<VBOType, Renderer::Geometry::Point2D> position{ 0 ,2, OpenGLUtils::Buffer::GLType::FLOAT, false };
		Renderer::GL::VertexAtributeObject::AttributePointer<VBOType, SphereSDF> sdfData{ 1,3, OpenGLUtils::Buffer::GLType::FLOAT, false };
		vao.EnableAndDefineAttributePointer(position);
		vao.EnableAndDefineAttributePointer(sdfData);
		vao.Unbind();

		vbo.SendDataGPU(OpenGLUtils::Buffer::BufferUsage::DYNAMIC_DRAW);
		ibo.SendDataGPU(OpenGLUtils::Buffer::BufferUsage::STATIC_DRAW);
	}
}

