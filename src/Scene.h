#pragma once

#include <iostream>
#include <functional>
#include "Log.h"
#include "Timer.h"

class Scene
{
public:
	Scene();
	virtual ~Scene() {
		Log::out << Log::Type::INFO << "Scene deleted: " + m_name + "\n";
	}

	virtual void OnInit() {}
	virtual void OnUpdate() {}
	virtual void OnDraw() {}

	void SetName(const std::string& name) { m_name = name; }
	std::string GetName() { return m_name; }
private:
	std::string m_name;
};