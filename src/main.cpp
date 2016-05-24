#include "ENOJ.h"
#include <json.hpp>

#include <lua.h>

class MainMenu : public Scene
{
public:
	virtual void OnInit()
	{
		try {
			Script::Load("Data/test.lua");
			Script::Get("objects")["first"]["GraphicsComponent"].ForAllStringKeys([](const std::string& key)
			{
				std::cout << key << "\n";
			});
		}
		catch (const std::exception& e) {
			std::cout << e.what() << "\n";
		}
	}

	virtual void OnUpdate() 
	{
		if (Input::GetKeyDown(Input::KEY_ESCAPE))
			Window::Close();
	}
	virtual void OnDraw() {}
};

void CreateWindow(const std::string& properties)
{
	try {
		json j = json::parse_file(properties);
		auto size = j["size"];
		auto vsync = j["vsync"];
		auto fullscreen = j["fullscreen"];

		if (size.is_null() || !size.is_array() || size.size() < 2) {
			if (!fullscreen.is_null() && fullscreen)
				Window::Create("ENOJ");
			else
				throw std::exception("window size wasn't specified");
		}
		else {
			Window::Create(size[0], size[1], "ENOJ", (!fullscreen.is_null() && fullscreen));
		}
	}
	catch (std::exception e) {
		Log::out << Log::Type::ERROR << e.what() << "\n";
		Window::Create(800, 600, "ENOJ");
	}
}

class TestGame : public Game
{
public:
	virtual void Init()
	{
		CreateWindow("config");

		Push(std::make_shared<MainMenu>());
	}
};

int main(int argc, char** argv)
{
	{
		TestGame game;
		game.Init();
		game.Loop();
	}

	return 0;
}