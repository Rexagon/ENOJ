#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <typeindex>

#include "ComponentManager.h"
#include "Transformable.h"
#include "Log.h"

namespace ecs
{
	class Entity : public Transformable
	{
	public:
		virtual ~Entity()
		{
			Log::out << Log::Type::INFO << "Entity deleted: " << m_name << "\n";
		}

		template<class T>
		void Assign(Component* component)
		{
			static_assert(std::is_base_of<Component, T>::value, "T must be derived from the Component class");
			m_components[std::type_index(typeid(T))] = component;
			component->m_owner = this;
		}

		template<class T>
		void AssignNew()
		{
			static_assert(std::is_base_of<Component, T>::value, "T must be derived from the Component class");
			T* component = ComponentManager::Create<T>();
			m_components[std::type_index(typeid(T))] = component;
			component->m_owner = this;
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

		template<class T>
		bool Has()
		{
			return m_components.find(std::type_index(typeid(T))) != m_components.end();
		}

		void SetName(const std::string& type) { m_name = type; }
		std::string GetName() const { return m_name; }
	private:
		std::string m_name;
		std::unordered_map<std::type_index, Component*> m_components;
	};
}