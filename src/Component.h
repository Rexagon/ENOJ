#pragma once

#include "Script.h"

namespace ecs
{
	class Entity;

	class Component
	{
	public:
		Component() {}
		Component(sel::Selector data) {}
		virtual ~Component() {}

		Entity* GetOwner() const { return m_owner; }
	protected:
		friend class Entity;

		Entity* m_owner;
	};
}