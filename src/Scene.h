#pragma once

#include <iostream>
#include <functional>
#include <memory>
#include <vector>
#include <json.hpp>

#include "Script.h"
#include "Entity.h"
#include "Timer.h"

#include "RenderingSystem.h"

class Scene
{
public:
	Scene();
	virtual ~Scene();

	static std::unique_ptr<Scene> Load(const std::string& filename);

	void AddEntity(json object);

	void OnInit();
	void OnUpdate();
	void OnDraw();

	void SetName(const std::string& name) { m_name = name; }
	std::string GetName() { return m_name; }
private:
	RenderingSystem m_renderingSystem;
	CameraSystem m_cameraSystem;

	std::vector<std::unique_ptr<ecs::Entity>> m_entities;
	std::string m_name;
};