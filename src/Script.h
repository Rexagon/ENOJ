#pragma once

#include <string>
#include <luacppinterface.h>

class Script
{
public:
	static std::string Load(const std::string& filename);
	static std::string Eval(const std::string& code);

	static LuaTable GetGlobal();

	static LuaTable CreateTable();

	template<class T>
	static LuaFunction<T> CreateFunction(const std::string& name)
	{
		return lua->CreateFunction<T>();
	}
private:
	friend class Game;

	static void Init();
	static void Close();

	static std::unique_ptr<Lua> lua;
};