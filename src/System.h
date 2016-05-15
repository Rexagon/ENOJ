#pragma once

#include <vector>
#include <memory>

#include "ComponentManager.h"

namespace ecs
{
	template<class T>
	class System : public ComponentManager
	{
	public:
		static_assert(std::is_base_of<Component, T>::value, "T must be derived from the Component class");

		static T* Create()
		{
			T* ptr = ComponentManager::Create<T>();
			m_components.push_back(ptr);
			return ptr;
		}
	protected:
		static std::vector<T*> m_components;
	};
}