#include <chaiscript\chaiscript.hpp>
#include "ChaiscriptBindings.h"



#define ADD_FUN(Class, Name) module->add(chaiscript::fun(&Class::Name), #Name )

std::shared_ptr<chaiscript::Module> CreateChaiscriptBindings()
{
	auto module = std::make_shared<chaiscript::Module>();


	
	return module;
}
