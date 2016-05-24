#pragma once

#include <string>
#include <selene.h>

class Script
{
public:
	static void Load(const std::string& filename);
	static void Eval(const std::string& code);
	static void GC();

	static sel::Selector Get(const std::string& name);
private:
	friend class Game;

	static void Init();
	static void Close();

	static sel::State m_state;
};