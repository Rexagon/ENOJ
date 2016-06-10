#include "Config.h"

#include <json.hpp>
#include "Log.h"

std::string Config::dataFolder = "Data/";

size_t Config::windowWidth = 1024;
size_t Config::windowHeight = 768;

bool Config::vsync = true;
bool Config::fullscreen = false;
bool Config::autosize = false;

void Config::Load(const std::string& filename)
{
	try {
		json j = json::parse_file(filename);

		auto dataFolderData = j["data_folder"];
		if (dataFolderData.is_string()) {
			dataFolder = dataFolderData;
		}

		auto sizeData = j["size"];
		if (sizeData.is_array() && sizeData.size() > 1) {
			windowWidth = sizeData[0];
			windowHeight = sizeData[1];
		}
		else {
			autosize = true;
		}

		auto vsyncData = j["vsync"];
		if (sizeData.is_boolean()) {
			vsync = sizeData;
		}

		auto fullscreenData = j["fullscreen"];
		if (fullscreenData.is_boolean()) {
			fullscreen = fullscreenData;
		}
	}
	catch (const std::exception& e) {
		Log::out << Log::Type::ERROR << e.what() << "\n";
		CreateFile(filename);
	}
}

void Config::CreateFile(const std::string & filename)
{
	json j;
	j["size"] = { windowWidth, windowHeight };
	j["vsync"] = vsync;
	j["fullscreen"] = fullscreen;
	j["data_folder"] = dataFolder;

	std::ofstream file(filename);
	file << j.dump();
	file.close();
}
