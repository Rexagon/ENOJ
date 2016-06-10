#include "CameraComponent.h"
#include "Log.h"
#include "Entity.h"

CameraComponent::~CameraComponent()
{
	Log::out << Log::Type::INFO << "Component deleted: " << m_owner->GetName() << ".camera_component\n";
}
