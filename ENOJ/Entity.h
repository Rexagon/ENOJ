#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <typeindex>

#include "ComponentManager.h"

namespace ecs
{
	class Entity
	{
	public:
		virtual ~Entity()
		{
#ifdef DEBUG
#include <iostream>
			std::cout << "Entity [" + m_type + "] deleted\n";
#endif
		}

		template<class T>
		void Assign(Component* component)
		{
			static_assert(std::is_base_of<Component, T>::value, "T must be derived from the Component class");
			m_components[std::type_index(typeid(T))] = component;
		}

		template<class T>
		void AssignNew()
		{
			static_assert(std::is_base_of<Component, T>::value, "T must be derived from the Component class");
			m_components[std::type_index(typeid(T))] = ComponentManager::Create<T>();
		}

		template<class T>
		T* Get()
		{
			auto it = m_components.find(std::type_index(typeid(T)));
			if (it != m_components.end()) {
				return dynamic_cast<T*>(it->second);
			}
			return nullptr;
		}

		void SetType(const std::string& type) { m_type = type; }
		std::string GetType() const { return m_type; }
	private:
		std::string m_type;
		std::unordered_map<std::type_index, Component*> m_components;
	};
}