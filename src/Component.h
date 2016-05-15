#pragma once

namespace ecs
{
	class Component
	{
	public:
		virtual ~Component() {}
	private:
		template<class T>
		friend class System;
	};
}