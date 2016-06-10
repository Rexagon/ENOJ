#include "CameraSystem.h"
#include "Log.h"
#include "Window.h"
#include "Entity.h"

void CameraSystem::Update(shader_ptr shader)
{
	if (m_currentCamera) {
		shader->SetUniform("camera_matrix", m_currentCamera->m_projection * m_currentCamera->GetOwner()->GetLookAtMatrix());
	}
}

CameraComponent* CameraSystem::Create(json data)
{
	auto component = ecs::System<CameraComponent>::Create();

	auto projection = data["projection"];
	if (!projection.is_string()) throw std::exception("Camera projection is not specified");
	std::string projectionType = projection;

	if (projectionType == "ortho") {

	}
	else if (projectionType == "perspective") {
		float fov = 60.0f;
		float nearPlane = 0.3f;
		float farPlane = 1000.0f;

		if (data["fov"].is_number()) {
			fov = data["fov"];
		}

		if (data["near_plane"].is_number()) {
			nearPlane = data["near_plane"];
		}

		if (data["far_plane"].is_number()) {
			farPlane = data["far_plane"];
		}

		component->m_projection = glm::perspective(glm::radians(fov), Window::GetAspect(), nearPlane, farPlane);

		m_currentCamera = component; //TODO: move it to function
	}
	else {
		Log::out << Log::Type::ERROR << "Unknown projection type: " + projectionType + "\n";
	}

	Log::out << Log::Type::INFO << "Component created: CameraComponent\n";

	return component;
}

void CameraSystem::Clear()
{
}

void CameraSystem::SetCurrentCamera(const std::string& name)
{
}
