#pragma once

namespace ecs
{
	class Component
	{
	public:
		virtual ~Component()
		{
#ifdef DEBUG
#include <iostream>
			std::cout << "Component deleted\n";
#endif
		}
	private:
		template<class T>
		friend class System;
	};
}