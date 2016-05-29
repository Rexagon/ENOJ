#pragma once

#include "Component.h"
#include "Model.h"

class RenderingComponent : public ecs::Component
{
public:
	~RenderingComponent();
private:
	friend class RenderingSystem;

	Model m_model;
};