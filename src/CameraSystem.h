#pragma once

#include <json.hpp>
#include "System.h"
#include "CameraComponent.h"
#include "ShaderManager.h"

class CameraSystem : public ecs::System<CameraComponent>
{
public:
	virtual void Update(shader_ptr shader);
	virtual CameraComponent* Create(json data);
	virtual void Clear();

	virtual void SetCurrentCamera(const std::string& name);
private:
	CameraComponent* m_currentCamera;
};