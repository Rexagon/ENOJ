#pragma once

#include "Math.h"

class Vertex
{
public:
	Vertex(const vec3& position, const vec2& texCoords = vec2(),
		const vec3& normal = vec3(0, 1, 0), const vec3& tangent = vec3()) :
		position(position), texCoords(texCoords), normal(normal), tangent(tangent), boneIds(ivec4()), weights(vec4(0.0f, 0.0f, 0.0f, 0.0f)) {}

	vec3 position;
	vec2 texCoords;
	vec3 normal;
	vec3 tangent;

	ivec4 boneIds;
	vec4 weights;
};