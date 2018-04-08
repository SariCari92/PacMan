#include "MiniginPCH.h"
#include "SceneObject.h"

dae::SceneObject::SceneObject()
	:m_pTransformComponent{std::make_shared<TransformComponent>()}
{

}
void dae::SceneObject::AddComponent(std::shared_ptr<ComponentBase> component)
{
	m_Components.push_back(component);
}
void dae::SceneObject::Update()
{
	for (std::shared_ptr<ComponentBase> component : m_Components)
	{
		component->Update();
	}
}
void dae::SceneObject::Render() const
{
	for (std::shared_ptr<ComponentBase> component : m_Components)
	{
		component->Render();
	}
}

std::shared_ptr<TransformComponent> dae::SceneObject::GetTransform() const
{
	return m_pTransformComponent;
}