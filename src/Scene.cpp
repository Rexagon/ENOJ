#include "Scene.h"

static size_t sceneCount = 0;

Scene::Scene() : m_name("scene_"+std::to_string(sceneCount))
{
	sceneCount++;
}
