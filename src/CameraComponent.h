#pragma once

#include "Component.h"
#include "Math.h"

class CameraComponent : public ecs::Component
{
public:
	~CameraComponent();
private:
	friend class CameraSystem;

	glm::mat4 m_projection;
};