#include "MiniginPCH.h"
#include "SceneObject.h"

dae::SceneObject::SceneObject()
	:m_pTransformComponent{std::make_shared<TransformComponent>()}
	,m_pParent{nullptr}
{
	std::unique_ptr<SceneObject> owner{ this };
	m_pTransformComponent->SetOwner(owner);
}

void dae::SceneObject::AddComponent(std::shared_ptr<ComponentBase> pComponent)
{
	m_Components.push_back(pComponent);
	pComponent->SetOwner(std::unique_ptr<SceneObject>(this));
}

void dae::SceneObject::Update()
{
	for (std::shared_ptr<ComponentBase> component : m_Components)
	{
		component->Update();
	}
	for (std::shared_ptr<SceneObject> child : m_Children)
	{
		child->Update();
	}
}

void dae::SceneObject::Render() const
{
	for (std::shared_ptr<ComponentBase> component : m_Components)
	{
		component->Render();
	}
	for (std::shared_ptr<SceneObject> child : m_Children)
	{
		child->Render();
	}
}

std::shared_ptr<TransformComponent> dae::SceneObject::GetTransform() const
{
	return m_pTransformComponent;
}

void dae::SceneObject::AddChild(std::shared_ptr<SceneObject> pChild)
{
	m_Children.push_back(pChild);
	pChild->m_pParent = std::unique_ptr<SceneObject>(this);
	auto parentPosition = m_pTransformComponent->GetWorldPosition();
	pChild->GetTransform()->Translate(parentPosition.x, parentPosition.y, parentPosition.z);
}

std::vector<std::shared_ptr<SceneObject>>& dae::SceneObject::GetChildren() 
{
	return m_Children;
}

