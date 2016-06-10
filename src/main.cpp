#include "ENOJ.h"

#include <json.hpp>

class TestGame : public Game
{
public:
	virtual void Init()
	{
		try {
			if (Config::autosize) {
				if (Config::fullscreen) {
					Window::Create("ENOJ");
				}
				else {
					throw std::exception("window size wasn't specified");
				}
			}
			else {
				Window::Create(Config::windowWidth, Config::windowHeight, "ENOJ", Config::fullscreen);
			}

			if (Config::vsync) {
				Window::EnableVSync();
			}
		}
		catch (const std::exception& e) {
			Log::out << Log::Type::ERROR << e.what() << "\n";
			Window::Create(800, 600, "ENOJ");
		}

		try {
			Push(Scene::Load(Config::dataFolder + "start_scene.json"));
		}
		catch (const std::exception& e) {
			Log::out << Log::Type::ERROR << e.what() << "\n";
		}
	}
};

int main(int argc, char** argv)
{
	Log::Create("log.txt");
	Config::Load("config");

	{
		TestGame game;
		game.Init();
		game.Loop();
	}

	Log::Close();

	return 0;
}