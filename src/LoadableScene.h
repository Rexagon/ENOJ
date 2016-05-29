#pragma once

#include "Scene.h"
#include "Script.h"
#include "Entity.h"

class LoadableScene : public Scene
{
public:
	static std::unique_ptr<LoadableScene> Load(const std::string& filename);

	virtual void OnInit();
	virtual void OnUpdate();
	virtual void OnDraw();

	void AddEntity(ecs::Entity* entity) { entities.push_back(entity); }
private:
	std::unique_ptr<sel::Selector> initFunction;
	std::unique_ptr<sel::Selector> updateFunction;
	std::unique_ptr<sel::Selector> drawFunction;

	std::vector<ecs::Entity*> entities;
};