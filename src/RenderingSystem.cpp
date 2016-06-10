#include "RenderingSystem.h"
#include "Log.h"
#include "ModelManager.h"
#include "Entity.h"
#include "CameraSystem.h"
#include "Config.h"


void RenderingSystem::Init(CameraSystem* cameraSystem)
{
	m_cameraSystem = cameraSystem;
	m_modelShader = ShaderManager::Create("Data/shaders/model", SHADER_VERTEX | SHADER_FRAGMENT);
	m_modelShader->Bind();
	m_modelShader->SetUniform("diffuse_tex", 0);
	m_modelShader->SetUniform("normal_tex", 1);
	m_modelShader->SetUniform("specular_tex", 2);
}

void RenderingSystem::Update()
{
	m_modelShader->Bind();
	m_cameraSystem->Update(m_modelShader);

	for (auto c : m_components) {
		c->m_model.Draw(m_modelShader, c->GetOwner()->GetTransformation());
	}
}

RenderingComponent* RenderingSystem::Create(json data)
{
	auto component = ecs::System<RenderingComponent>::Create();

	auto modelData = data["model"];
	if (modelData.is_string()) {
		try {
			std::string modelPath = data["model"];
			component->m_model = ModelManager::Get(Config::dataFolder + modelPath);
		}
		catch(const std::exception& e) {
			Log::out << Log::Type::ERROR << e.what() << "\n";
		}
	}

	Log::out << Log::Type::INFO << "Component created: RenderingComponent\n";

	return component;
}

void RenderingSystem::Clear()
{
	m_modelShader.reset();
}
