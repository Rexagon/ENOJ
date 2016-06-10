#pragma once

#include "Math.h"

class Transformable
{
public:
	Transformable() :m_position(glm::vec3()), m_rotation(glm::quat()), m_scale(glm::vec3(1.0f)) {}
	Transformable(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) :
		m_position(position), m_rotation(rotation), m_scale(scale) {}
	Transformable(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale) :
		m_position(position), m_rotation(rotation), m_scale(scale) {}

	glm::mat4 GetTransformation() const 
	{ 
		glm::mat4 translation = glm::translate(-m_position);
		glm::mat4 rotation = glm::mat4_cast(m_rotation);
		glm::mat4 scale = glm::scale(1.0f / m_scale);

		return scale * rotation * translation;
	}

	glm::mat4 GetLookAtMatrix() const
	{
		return glm::lookAt(m_position, m_position + GetDirection(), glm::vec3(0, 1, 0));
	}

	void SetPosition(float x, float y, float z) { m_position = glm::vec3(x, y, z); }
	void SetPosition(const glm::vec3& v) { m_position = v; }

	void Move(float x, float y, float z) { m_position += glm::vec3(x, y, z); }
	void Move(const glm::vec3& v) { m_position += v; }

	glm::vec3 GetPosition() const { return m_position; }

	void SetRotation(float x, float y, float z) { m_rotation = glm::quat(glm::radians(glm::vec3(x, y, z))); }
	void SetRotation(const glm::vec3& r) { m_rotation = glm::quat(r); }
	void SetRotation(const glm::quat& q) { m_rotation = q; }

	void Rotate(float x, float y, float z) { m_rotation = glm::quat(glm::vec3(x, y, z)) * m_rotation; }
	void Rotate(const glm::vec3& r) { m_rotation = glm::quat(r) * m_rotation; }
	void Rotate(const glm::quat& q) { m_rotation = q * m_rotation; }

	glm::quat GetRotation() const { return m_rotation; }

	void Scale(float k) { m_scale *= k; }
	void Scale(float x, float y, float z) { m_scale *= glm::vec3(x, y, z); }
	void Scale(const glm::vec3& v) { m_scale *= v; }

	void SetScale(float k) { m_scale = glm::vec3(k); }
	void SetScale(float x, float y, float z) { m_scale = glm::vec3(x, y, z); }
	void SetScale(const glm::vec3& v) { m_scale = v; }

	glm::vec3 GetScale() const { return m_scale; }
	
	glm::vec3 GetDirection() const { return m_rotation * glm::vec3(0.0f, 0.0f, 1.0f); }
private:
	glm::vec3 m_position;
	glm::quat m_rotation;
	glm::vec3 m_scale;
};