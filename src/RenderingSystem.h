#pragma once

#include <json.hpp>
#include "System.h"
#include "RenderingComponent.h"
#include "CameraSystem.h"

class RenderingSystem : public ecs::System<RenderingComponent>
{
public:
	void Init(CameraSystem* cameraSystem);
	virtual void Update();
	virtual RenderingComponent* Create(json data);
	virtual void Clear();
private:
	shader_ptr m_modelShader;
	CameraSystem* m_cameraSystem;
};