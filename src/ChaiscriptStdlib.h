#pragma once

namespace chaiscript {
	class Module;
}

std::shared_ptr<chaiscript::Module> create_chaiscript_stdlib();
