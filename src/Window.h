#pragma once

#include <iostream>
#include <SDL\SDL.h>

#include "Math.h"

class Window
{
public:
	static void CreateFromFile(const std::string& properties);

	static void Create(const std::string& title);
	static void Create(size_t width, size_t height, const std::string& title, bool fullscreen = false);
	static void Close();

	static void EnableVSync();
	static void DisableVSync();

	static void Clear();
	static void Clear(float r, float g, float b, float a);
	static void Update();

	static void BindForReading(size_t id);
	static void BindForDrawing();

	static std::string GetTitle() { return m_title; }
	static glm::ivec2 GetSize() { return m_size; }
	static float GetAspect() { return m_aspect; }
	static bool IsOpen() { return m_isOpen; }

	static void SetClearColor(const glm::vec3& color) { m_clearColor = color; }
	static glm::vec3 GetClearColor() { return m_clearColor; }

	static void SetMousePosition(int x, int y);
private:
	static glm::ivec2 m_size;
	static std::string m_title;
	static float m_aspect;
	static glm::vec3 m_clearColor;
	static bool m_isOpen;

	static SDL_Window* m_window;
	static SDL_GLContext m_context;
};