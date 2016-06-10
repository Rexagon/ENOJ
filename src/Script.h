#pragma once

#include <string>

class Script
{
public:
	static void Load(const std::string& filename);
	static void Run(const std::string& code);

	friend class Game;

	static void Init(Game* game);
	static void Close();
};