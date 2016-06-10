#include <chaiscript\chaiscript.hpp>
#include "ChaiscriptStdlib.h"
#include "ChaiscriptBindings.h"
#include "ÑhaiscriptCreator.h"

std::unique_ptr<chaiscript::ChaiScript> CreateChaiscript()
{
	auto chai = std::unique_ptr<chaiscript::ChaiScript>(new chaiscript::ChaiScript(create_chaiscript_stdlib()));
	chai->add(CreateChaiscriptBindings());
	return chai;
}