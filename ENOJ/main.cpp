#include <iostream>
#include <ctime>

#include "ENOJ.h"

class TestComponent : public ecs::Component
{
public:
	void SetPhrase(const std::string& phrase) 
	{
		m_phrase = phrase;
	}

	std::string GetPhrase() const 
	{
		return m_phrase;
	}
private:
	std::string m_phrase;
};

class AnotherTestComponent : public ecs::Component
{
public:
	void SetPhraseAbc(const std::string& phrase)
	{
		m_phrase = phrase;
	}

	std::string GetPhraseAbc() const
	{
		return m_phrase;
	}
private:
	std::string m_phrase;
};

class TestSystem : public ecs::System<TestComponent>
{
public:
	static void Update()
	{
	}
};

class MainMenu : public Scene
{
public:
	virtual void OnInit()
	{

	}

	virtual void OnUpdate()
	{
		TestSystem::Update();
	}

	virtual void OnDraw()
	{

	}
};

class TestGame : public Game
{
public:
	virtual void Init()
	{
		srand(static_cast<size_t>(time(nullptr)));

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

	ecs::ComponentManager::Clear();

	Log::Close();

#ifdef DEBUG
	std::cin.get();
#endif

	return 0;
}