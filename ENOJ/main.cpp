#include <iostream>
#include <ctime>

#include "ENOJ.h"

class MainMenu : public Scene
{
public:
	virtual void OnInit()
	{

	}

	virtual void OnUpdate()
	{

	}

	virtual void OnDraw()
	{

	}

	shader_ptr sh1;
	shader_ptr sh2;

	texture_ptr tx1;
	texture_ptr tx2;
};

class TestGame : public Game
{
public:
	virtual void Init()
	{
		srand(static_cast<size_t>(time(0)));

		Window::Create(800, 600, "ENOJ");
		Window::EnableVSync();

		this->Push(std::make_shared<MainMenu>());
	}
};

int main(int argc, char** argv)
{
	Log::Create("log.txt");

	{
		TestGame testGame;
		testGame.Init();
		testGame.Loop();
	}

	Log::Close();

	return 0;
}