#include "MiniginPCH.h"
#include "SceneObject.h"
#include "ThreadWrapper.h"

dae::SceneObject::SceneObject()
	:m_pTransformComponent{ std::make_shared<TransformComponent>()}
	,m_pParent{nullptr}, m_pScene{nullptr}
{
	m_pTransformComponent->SetOwner(this);
}

dae::SceneObject::~SceneObject()
{
	std::cout << "SceneObject Destructor Called!" << std::endl;
}

void dae::SceneObject::AddComponent(std::shared_ptr<ComponentBase> pComponent)
{
	m_Components.push_back(pComponent);
	pComponent->SetOwner(this);
}

void dae::SceneObject::Update(float deltaTime)
{
	for (std::shared_ptr<ComponentBase> component : m_Components)
	{
		component->Update(deltaTime);

	}
	for (std::shared_ptr<SceneObject> child : m_Children)
	{
		child->Update(deltaTime);

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
	pChild->m_pParent = this;
	auto parentPosition = m_pTransformComponent->GetWorldPosition();
	pChild->GetTransform()->Translate(parentPosition.x, parentPosition.y, parentPosition.z);
}

std::vector<std::shared_ptr<dae::SceneObject>>& dae::SceneObject::GetChildren() 
{
	return m_Children;
}

dae::SceneObject* dae::SceneObject::GetParent() const
{
	return m_pParent;
}

void dae::SceneObject::SetScene(dae::Scene *scene)
{
	m_pScene = &*scene;
}

dae::Scene* dae::SceneObject::GetScene() const
{
	return m_pScene;
}
