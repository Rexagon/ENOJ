#include "RenderingComponent.h"
#include "Log.h"
#include "Entity.h"

RenderingComponent::~RenderingComponent()
{
	Log::out << Log::Type::INFO << "Component deleted: " << m_owner->GetName() << ".rendering_component\n";
}
