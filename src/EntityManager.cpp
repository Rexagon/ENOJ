#include "EntityManager.h"
#include "Script.h"
#include "Log.h"

#include "RenderingSystem.h"

std::vector<std::unique_ptr<ecs::Entity>> ecs::EntityManager::m_components;

void ecs::EntityManager::Clear()
{
	m_components.clear();
}

ecs::Entity* ecs::EntityManager::Create()
{
	m_components.push_back(std::make_unique<Entity>());
	return m_components.back().get();
}

ecs::Entity* ecs::EntityManager::Create(const std::string& name)
{
	m_components.push_back(std::make_unique<Entity>());
	auto e = m_components.back().get();

	auto object = Script::Get("objects")[name];
	e->SetName(object["name"]);

	object.ForAllKeys([&](const std::string& key) {
		if (key == "rendering_component") {
			auto component = RenderingSystem::Create(object[key.c_str()]);
			e->Assign<RenderingComponent>(component);
		}
	});

	Log::out << Log::Type::INFO << "Entity created: " << e->GetName() << "\n";

	return e;
}
