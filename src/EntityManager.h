#pragma once

#include <vector>
#include <memory>

#include "Entity.h"

namespace ecs
{
	class EntityManager
	{
	public:
		static void Clear();
		static Entity* Create();
		static Entity* Create(const std::string& name);
	private:
		static std::vector<std::unique_ptr<Entity>> m_components;
	};
}