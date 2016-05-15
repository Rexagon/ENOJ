#pragma once

class Timer
{
public:
	static void Update();
	static float deltaTime();
private:
	static uint64_t m_prevFrame;
	static uint64_t m_currentFrame;
	static float m_deltaTime;
};