#include "Window.h"

#include <cassert>
#include <GL\glew.h>

#include "Log.h"

glm::ivec2 Window::m_size;
std::string Window::m_title;
float Window::m_aspect = 0;
glm::vec3 Window::m_clearColor = glm::vec3(0.2f, 0.2f, 0.2f);
bool Window::m_isOpen = false;

SDL_Window* Window::m_window = nullptr;
SDL_GLContext Window::m_context = 0;

void Window::Create(const std::string & title)
{
	SDL_DisplayMode display;
	SDL_GetCurrentDisplayMode(0, &display);
	std::cout << display.w << " " << display.h << "\n";
	Create(display.w, display.h, title, true);
}

void Window::Create(size_t width, size_t height, const std::string & title, bool fullscreen)
{
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	m_aspect = static_cast<float>(width) / static_cast<float>(height);
	m_size = glm::ivec2(width, height);

	if (!fullscreen)
		m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	else 
		m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);

	m_context = SDL_GL_CreateContext(m_window);

	GLenum res = glewInit();
	if (res != GLEW_OK) {
		throw std::exception("Glew failed to initialize!");
	}

	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);

	m_isOpen = true;
}

void Window::Close()
{
	SDL_GL_DeleteContext(m_context);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
	m_isOpen = false;
}

void Window::EnableVSync()
{
	SDL_GL_SetSwapInterval(1);
}

void Window::DisableVSync()
{
	SDL_GL_SetSwapInterval(0);
}

void Window::Clear()
{
	glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, 1.0f);
	glViewport(0, 0, m_size.x, m_size.y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glCullFace(GL_FRONT);
}

void Window::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glViewport(0, 0, m_size.x, m_size.y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glCullFace(GL_BACK);
}

void Window::Update()
{
	SDL_GL_SwapWindow(m_window);
}

void Window::BindForReading(size_t id)
{
	glActiveTexture(GL_TEXTURE0 + id);
}

void Window::BindForDrawing()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Window::SetMousePosition(int x, int y)
{
	SDL_WarpMouseInWindow(m_window, x, y);
}