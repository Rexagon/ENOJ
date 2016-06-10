#include "Scene.h"

#include "RenderingComponent.h"

static size_t sceneCount = 0;

Scene::Scene() : m_name("scene_"+std::to_string(sceneCount))
{
	sceneCount++;
}

Scene::~Scene()
{
	Log::out << Log::Type::INFO << "Scene deleted: " + m_name + "\n";
}

std::unique_ptr<Scene> Scene::Load(const std::string& filename)
{
	json j = json::parse_file(filename);
	auto scene = std::make_unique<Scene>();

	auto nameData = j["name"];
	if (nameData.is_string()) {
		scene->SetName(nameData);
	}

	auto scriptsData = j["scripts"];
	if (scriptsData.is_array()) {
		//TODO: add scripts handling
	}

	auto entitiesData = j["entities"];
	if (entitiesData.is_array()) {
		for (auto entity : entitiesData) {
			if (entity.is_object()) {
				scene->AddEntity(entity);
			}
		}
	}

	return scene;
}

void Scene::AddEntity(json j)
{
	auto entity = std::make_unique<ecs::Entity>();

	std::string name;
	auto nameData = j["name"];
	if (nameData.is_string()) {
		name = nameData;
	}
	else {
		name = "entity_" + std::to_string(m_entities.size());
	}
	entity->SetName(name);

	auto positionData = j["position"];
	if (positionData.is_array() && positionData.size() == 3) {
		glm::vec3 position;
		size_t i = 0;
		bool success = true;
		for (auto& c : positionData) {
			if (!c.is_number()) {
				success = false;
				break;
			}
			position[i] = c;
			++i;
		}
		if (success) {
			entity->SetPosition(position);
		}
	}

	auto rotationData = j["rotation"];
	if (rotationData.is_array() && rotationData.size() == 3) {
		glm::vec3 rotation;
		size_t i = 0;
		bool success = true;
		for (auto& c : rotationData) {
			if (!c.is_number()) {
				success = false;
				break;
			}
			rotation[i] = glm::radians(static_cast<float>(c));
			++i;
		}
		if (success) {
			entity->SetRotation(rotation);
		}
	}

	auto scaleData = j["scale"];
	if (scaleData.is_array() && rotationData.size() == 3) {
		glm::vec3 scale;
		size_t i = 0;
		bool success = true;
		for (auto& c : scaleData) {
			if (!c.is_number()) {
				success = false;
				break;
			}
			scale[i] = c;
			++i;
		}
		if (success) {
			entity->SetScale(scale);
		}
	}
	else if (scaleData.is_number()) {
		entity->SetScale(static_cast<float>(scaleData));
	}

	auto renderingComponentData = j["rendering_component"];
	if (renderingComponentData.is_object()) {
		entity->Assign<RenderingComponent>(m_renderingSystem.Create(renderingComponentData));
	}

	auto cameraComponentData = j["camera_component"];
	if (cameraComponentData.is_object()) {
		entity->Assign<CameraComponent>(m_cameraSystem.Create(cameraComponentData));
	}

	Log::out << Log::Type::INFO << "Entity created: " << name << "\n";

	m_entities.push_back(std::move(entity));
}

void Scene::OnInit()
{
	m_renderingSystem.Init(&m_cameraSystem);
}

void Scene::OnUpdate()
{

}

void Scene::OnDraw()
{


	m_renderingSystem.Update();
}
