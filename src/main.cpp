#include "ENOJ.h"

class MainMenu : public Scene
{
public:
	virtual void OnInit()
	{
		Script::GetGlobal().Set("objects", Script::CreateTable());

		Script::Load("test.lua"); 
		Script::Load("testB.lua");

		Script::GetGlobal().Get<LuaTable>("objects").ForAllStringKeys([](std::string key, LuaType::Value value) {
			std::cout << key << "\n";
		});
	}

	virtual void OnUpdate() {}
	virtual void OnDraw() {}
};

class TestGame : public Game
{
public:
	virtual void Init()
	{
		Window::Create(800, 600, "ENOJ");
		Window::EnableVSync();

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