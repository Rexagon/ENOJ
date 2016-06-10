#include <chaiscript\chaiscript_stdlib.hpp>
#include "ChaiscriptStdlib.h"

std::shared_ptr<chaiscript::Module> create_chaiscript_stdlib()
{
	return chaiscript::Std_Lib::library();
}
