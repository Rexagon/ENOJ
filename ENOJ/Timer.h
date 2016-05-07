#pragma once

class Timer
{
public:
	static void Update();
	static float deltaTime();
	static float currentTime();
private:
	static long m_prevFrame;
	static long m_currentFrame;
	static float m_deltaTime;
};