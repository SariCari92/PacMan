#include "MiniginPCH.h"
#include  "TransformComponent.h"
#include "SceneObject.h"

TransformComponent::TransformComponent()
	: m_RelativePosition{}
	, m_WorldPosition{}
	, m_pOwner{}
{

}

TransformComponent::~TransformComponent()
{
	std::cout << "TransformComponent Destructor Called!" << std::endl;	
}

void TransformComponent::SetWorldPosition(const glm::vec3 newPos)
{
	glm::vec3 oldPos = m_WorldPosition;
	m_WorldPosition = newPos;
	glm::vec3 translation = newPos - oldPos;

	std::vector<std::shared_ptr<dae::SceneObject>> children = m_pOwner->GetChildren();
	for (auto child : children)
	{
		child->GetTransform()->Translate(translation);
	}

	dae::SceneObject *pParent = m_pOwner->GetParent();
	if (pParent)
	{
		glm::vec3 parentWorldPosition = pParent->GetTransform()->GetWorldPosition();
		m_RelativePosition = m_WorldPosition - parentWorldPosition;
	}
	else
	{
		m_RelativePosition = m_WorldPosition;
	}
}
glm::vec3 TransformComponent::GetWorldPosition() const
{

	return m_WorldPosition;
}
void TransformComponent::SetRelativePosition(const glm::vec3 newPos)
{
	dae::SceneObject *pParent = m_pOwner->GetParent();
	if (pParent == nullptr)
	{
		SetWorldPosition(newPos);
	}
	else
	{
		glm::vec3 oldPos = m_RelativePosition;
		m_RelativePosition = newPos;
		glm::vec3 translation = newPos - oldPos;
		m_WorldPosition += translation;

		std::vector<std::shared_ptr<dae::SceneObject>> children = m_pOwner->GetChildren();
		for (auto child : children)
		{
			child->GetTransform()->Translate(translation);
		}
	}


}
glm::vec3 TransformComponent::GetRelativePosition() const
{
	return m_RelativePosition;
}

void TransformComponent::Translate(float x, float y, float z)
{
	m_WorldPosition.x += x;
	m_WorldPosition.y += y;
	m_WorldPosition.z += z;

	std::vector<std::shared_ptr<dae::SceneObject>> children = m_pOwner->GetChildren();
	for (auto child : children)
	{
		child->GetTransform()->Translate(x, y, z);
	}

	dae::SceneObject *pParent = m_pOwner->GetParent();
	if (pParent)
	{
		glm::vec3 parentWorldPosition = pParent->GetTransform()->GetWorldPosition();
		m_RelativePosition = m_WorldPosition - parentWorldPosition;
	}

}

void TransformComponent::Translate(glm::vec3 translation)
{
	m_WorldPosition += translation;

	std::vector<std::shared_ptr<dae::SceneObject>> children = m_pOwner->GetChildren();
	for (auto child : children)
	{
		child->GetTransform()->Translate(translation);
	}

	dae::SceneObject *pParent = m_pOwner->GetParent();
	if (pParent)
	{
		glm::vec3 parentWorldPosition = pParent->GetTransform()->GetWorldPosition();
		m_RelativePosition = m_WorldPosition - parentWorldPosition;
	}
}

void TransformComponent::SetOwner(dae::SceneObject *pOwner)
{
	m_pOwner = pOwner;
}


