#include "LoadableScene.h"

#include <json.hpp>

#include "RenderingSystem.h"

std::unique_ptr<LoadableScene> LoadableScene::Load(const std::string & filename)
{
	json j = json::parse_file(filename);
	auto scene = std::make_unique<LoadableScene>();
	scene->SetName(j["name"]);
	std::string path = j["script"];
	Script::Load(filename.substr(0, filename.find_last_of('/') + 1) + path);
	scene->initFunction = std::make_unique<sel::Selector>(Script::Get("scenes")[scene->GetName()]["on_init"]);
	scene->updateFunction = std::make_unique<sel::Selector>(Script::Get("scenes")[scene->GetName()]["on_update"]);
	scene->drawFunction = std::make_unique<sel::Selector>(Script::Get("scenes")[scene->GetName()]["on_draw"]);
	return scene;
}

void LoadableScene::OnInit()
{
	if (initFunction) {
		(*initFunction)();
	}
}

void LoadableScene::OnUpdate()
{
	if (updateFunction) {
		(*updateFunction)((double)Timer::deltaTime());
	}
}

void LoadableScene::OnDraw()
{
	if (drawFunction) {
		(*drawFunction)((double)Timer::deltaTime());
	}
	RenderingSystem::Update();
}
