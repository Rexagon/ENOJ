#include "ComponentManager.h"

std::vector<std::unique_ptr<ecs::Component>> ecs::ComponentManager::m_components;

void ecs::ComponentManager::Clear()
{
	m_components.clear();
}
