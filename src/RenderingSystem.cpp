#include "RenderingSystem.h"
#include "Log.h"
#include "ModelManager.h"
#include "Entity.h"

std::vector<RenderingComponent*> ecs::System<RenderingComponent>::m_components;
shader_ptr RenderingSystem::m_modelShader = nullptr;

void RenderingSystem::Init()
{
	m_modelShader = ShaderManager::Create("Data/shaders/model", SHADER_VERTEX | SHADER_FRAGMENT);
}

void RenderingSystem::Update()
{
	auto shader = ShaderManager::Get("Data/shaders/model");

	for (auto c : m_components) {
		c->m_model.Draw(shader, c->GetOwner()->GetTransformation());
	}
}

RenderingComponent * RenderingSystem::Create(sel::Selector data)
{
	auto component = ecs::System<RenderingComponent>::Create();
	
	try {
		component->m_model = ModelManager::Get(data["model"]);
	}
	catch (const std::exception& e) {
		Log::out << Log::Type::ERROR << e.what() << "\n";
	}

	Log::out << Log::Type::INFO << "Component created: RenderingComponent\n";

	return component;
}
