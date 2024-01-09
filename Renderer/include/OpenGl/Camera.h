#pragma once

#include "Type/Transform.h"
#include <type_traits>
namespace Renderer::GL {

	//CRTP
	template<typename T>
	class BaseCamera {
	public:
		BaseCamera() = default;

		void Translate(const vec3& translation)
		{
			transform.position += translation;
		}
		void Rotate(const vec3& axis, float degrees)
		{
			auto rotation = axis * degrees;
			transform.eulerRotation += rotation;
		}

		mat4 GetCameraViewMatrix() const
		{
			return static_cast<mat4>(transform);
		}
		mat4 GetProjectionMatrix() const
		{
			return static_cast<const T*>(this)->GetProjectionMatrixImpl();
		}

		std::tuple<mat4, mat4> GetCameraAndProjectionMatrices()const {
			return { GetCameraViewMatrix(), GetProjectionMatrix() };
		}

	private:
		::Core::Transform transform;
	};


	class OrthoCamera : public BaseCamera<OrthoCamera>
	{
	public:
		OrthoCamera(float width, float height, float near, float far) : frustum(width, height), plane(near, far) {}
		mat4 GetProjectionMatrixImpl()const
		{
			return glm::ortho(0.f, frustum.x, 0.f, frustum.y, plane.x, plane.y);
		}

	private:
		vec2 frustum;
		vec2 plane;
	};

}