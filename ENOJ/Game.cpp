#include "Game.h"
#include "Window.h"
#include "Input.h"
#include "TextureManager.h"
#include "ShaderManager.h"

Game::Game()
{
}

Game::~Game()
{
	while (!m_scenes.empty())
	{
		m_scenes.pop();
	}

	TextureManager::Clear();
	ShaderManager::Clear();
}

void Game::Init()
{
}

void Game::Loop()
{
	while (Window::IsOpen())
	{
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
	m_currentScene->OnInit();
}

void Game::Pop()
{
	m_scenes.pop();
	if (m_scenes.empty()) 
	{
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
