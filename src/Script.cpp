#include "Script.h"

#include <fstream>
#include <streambuf>

#include "Constants.h"

std::unique_ptr<Lua> Script::lua = nullptr;

std::string Script::Load(const std::string& filename)
{
	std::ifstream file(Constants::DATA_FOLDER + filename);
	std::string code((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	return lua->RunScript(code);
}

std::string Script::Eval(const std::string& code)
{
	return lua->RunScript(code);
}

LuaTable Script::GetGlobal()
{
	return lua->GetGlobalEnvironment();
}

LuaTable Script::CreateTable()
{
	return lua->CreateTable();
}

void Script::Init()
{
	lua = std::make_unique<Lua>();
	lua->LoadStandardLibraries();
}

void Script::Close()
{
	lua->CollectGarbage();
}