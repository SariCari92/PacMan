#include "MiniginPCH.h"
#include "SceneObject.h"

void dae::SceneObject::AddComponent(std::shared_ptr<ComponentBase> component)
{
	m_Components.push_back(component);
}