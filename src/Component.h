#pragma once

namespace ecs
{
	class Entity;

	class Component
	{
	public:
		virtual ~Component() {}
	private:		
		friend class Entity;

		Entity* m_owner;
	};
}