#pragma once

#include <memory>
#include <stack>

#include "Scene.h"

class Game
{
public:
	Game();
	virtual ~Game();

	virtual void Init() {}
	virtual void Loop();

	void Push(std::shared_ptr<Scene> scene);
	void Pop();
	std::shared_ptr<Scene> PeekScene();
private:
	std::shared_ptr<Scene> m_currentScene;
	std::stack<std::shared_ptr<Scene>> m_scenes;
};