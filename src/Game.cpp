#include "Game.h"
#include "Window.h"
#include "Input.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "ComponentManager.h"
#include "Constants.h"
#include "Script.h"

#include <ctime>

Game::Game()
{
	Log::Create(Constants::LOG_FILE_NAME);
	srand(static_cast<size_t>(time(nullptr)));

	Script::Init();
}

Game::~Game()
{
	while (!m_scenes.empty()) {
		m_scenes.pop();
	}

	TextureManager::Clear();
	ShaderManager::Clear();
	ecs::ComponentManager::Clear();

	Script::Close();
	Log::Close();
}

void Game::Loop()
{
	while (Window::IsOpen()) {
		Input::Update();
		if (!m_currentScene) continue;

		m_currentScene->OnUpdate();
		if (!Window::IsOpen()) break;

		Window::Clear();
		m_currentScene->OnDraw();
		Window::Update();
	}
}

void Game::Push(std::shared_ptr<Scene> scene)
{
	m_scenes.push(scene);
	m_currentScene = scene;
	scene->OnInit();
}

void Game::Pop()
{
	m_scenes.pop();
	if (m_scenes.empty())  {
		m_currentScene = nullptr;
	}
	else {
		m_currentScene = m_scenes.top();
	}
}

std::shared_ptr<Scene> Game::PeekScene()
{
	return m_currentScene;
}
