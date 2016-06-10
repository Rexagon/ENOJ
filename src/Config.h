#pragma once

#include <string>

class Config
{
public:
	static void Load(const std::string& filename);
	static void CreateFile(const std::string& filename);

	static std::string dataFolder;

	static size_t windowWidth;
	static size_t windowHeight;

	static bool vsync;
	static bool fullscreen;
	static bool autosize;
};