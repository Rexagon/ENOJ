#include <SDL\SDL.h>

#include "timer.h"

uint64_t Timer::m_prevFrame = 0;
uint64_t Timer::m_currentFrame = 0;
float Timer::m_deltaTime = 0.0f;

void Timer::Update()
{
	m_deltaTime = 0.0f;
	m_currentFrame = SDL_GetPerformanceCounter();
	int deltaTicks = (int)(m_currentFrame - m_prevFrame);
	m_deltaTime = (float)deltaTicks / SDL_GetPerformanceFrequency();
	m_prevFrame = m_currentFrame;
}

float Timer::deltaTime()
{
	float dt = m_deltaTime;
	if (dt <= 0.0f || dt > 1.0f) {
		dt = 0.025f;
	}

	return dt;
}