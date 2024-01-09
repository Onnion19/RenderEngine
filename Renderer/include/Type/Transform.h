#pragma once 

#include "Core/types.h"
#include "gtc/matrix_transform.hpp"

namespace Core {
	struct Transform {
		vec3 position = vec3{ 0.f };
		vec3 eulerRotation = vec3{ 0.f };
		vec3 size = vec3{ 1.f };

		explicit operator mat4() const {
			mat4 matrix = glm::identity<mat4>();
			matrix = glm::translate(matrix, position);
			matrix = glm::rotate(matrix, glm::radians(eulerRotation.z), { 0.f, 0.f, 1.f });
			matrix = glm::rotate(matrix, glm::radians(eulerRotation.y), { 0.f, 1.f, 0.f });
			matrix = glm::rotate(matrix, glm::radians(eulerRotation.x), { 1.f, 0.f, 0.f });
			matrix = glm::scale(matrix, size);
			return matrix;
		}
	};
}