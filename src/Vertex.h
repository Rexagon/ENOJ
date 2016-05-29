#pragma once

#include "Math.h"

struct Vertex
{
	Vertex(const glm::vec3& position = glm::vec3(), 
		   const glm::vec2& texCoords = glm::vec2(), 
		   const glm::vec3& normal = glm::vec3(0, 1, 0), 
		   const glm::vec3& tangent = glm::vec3()) 
		:
			position(position),
			texCoords(texCoords),
			normal(normal),
			tangent(tangent),
			boneIds(glm::ivec4()),
			weights(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)) {}

	glm::vec3 position;
	glm::vec2 texCoords;
	glm::vec3 normal;
	glm::vec3 tangent;

	glm::ivec4 boneIds;
	glm::vec4 weights;
};