#include "Input.h"
#include "Window.h"
#include <SDL\SDL.h>

const static int NUM_KEYS = 512;
const static int NUM_MOUSEBUTTONS = 256;

static SDL_Event e;

static int mouseX = 0;
static int mouseY = 0;

static bool inputs[NUM_KEYS];
static bool downKeys[NUM_KEYS];
static bool upKeys[NUM_KEYS];

static bool mouseInput[NUM_MOUSEBUTTONS];
static bool downMouse[NUM_MOUSEBUTTONS];
static bool upMouse[NUM_MOUSEBUTTONS];

void Input::Update()
{
	for (int i = 0; i < NUM_MOUSEBUTTONS; i++)
	{
		downMouse[i] = false;
		upMouse[i] = false;
	}

	for (int i = 0; i < NUM_KEYS; i++)
	{
		downKeys[i] = false;
		upKeys[i] = false;
	}

	while (SDL_PollEvent(&e))
	{
		int value = 0;

		switch (e.type)
		{
		case SDL_QUIT:
			Window::Close();
			break;
		case SDL_MOUSEMOTION:
			mouseX = e.motion.x;
			mouseY = e.motion.y;
			break;
		case SDL_KEYDOWN:
			value = e.key.keysym.scancode;
			inputs[value] = true;
			downKeys[value] = true;
			break;
		case SDL_KEYUP:
			value = e.key.keysym.scancode;
			inputs[value] = false;
			upKeys[value] = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			value = e.button.button;
			mouseInput[value] = true;
			downMouse[value] = true;
			break;
		case SDL_MOUSEBUTTONUP:
			value = e.button.button;
			mouseInput[value] = false;
			upMouse[value] = true;
			break;
		default:
			break;
		}
	}
}

bool Input::GetKey(int keyCode)
{
	return inputs[keyCode];
}

bool Input::GetKeyDown(int keyCode)
{
	return downKeys[keyCode];
}

bool Input::GetKeyUp(int keyCode)
{
	return upKeys[keyCode];
}

bool Input::GetMouse(int button)
{
	return mouseInput[button];
}

bool Input::GetMouseDown(int button)
{
	return downMouse[button];
}

bool Input::GetMouseUp(int button)
{
	return upMouse[button];
}

vec2 Input::GetMousePosition()
{
	return vec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
}

void Input::SetCursor(bool visible)
{
	if (visible)
		SDL_ShowCursor(1);
	else
		SDL_ShowCursor(0);
}

void Input::SetMousePosition(const vec2& pos)
{
	Window::SetMousePosition(static_cast<int>(pos.x), static_cast<int>(pos.y));
}