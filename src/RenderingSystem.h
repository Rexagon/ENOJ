#pragma once

#include "System.h"
#include "RenderingComponent.h"

class RenderingSystem : public ecs::System<RenderingComponent>
{
public:
	static void Init();
	static void Update();
	static RenderingComponent* Create(sel::Selector data);

	static shader_ptr m_modelShader;
};