#include "ENOJ.h"

#include <lua.h>

class TestGame : public Game
{
public:
	virtual void Init()
	{
		Window::CreateFromFile("config.json");

		auto scene = LoadableScene::Load("Data/main_menu.json");
		Script::Get("objects").ForAllKeys([&](const std::string& key) {
			scene->AddEntity(ecs::EntityManager::Create(key));
		});
		Push(std::move(scene));
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