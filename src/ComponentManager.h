#pragma once

#include <vector>
#include <memory>

#include "Component.h"

namespace ecs
{
	class ComponentManager
	{
	public:
		static void Clear();
	protected:
		template<class T>
		static T* Create()
		{
			m_components.push_back(std::make_unique<T>());
			return dynamic_cast<T*>(m_components.back().get());
		}
	private:
		friend class Entity;

		static std::vector<std::unique_ptr<Component>> m_components;
	};
}