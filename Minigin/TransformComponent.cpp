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
	m_WorldPosition = newPos;
}
glm::vec3 TransformComponent::GetWorldPosition() const
{
	return m_WorldPosition;
}
void TransformComponent::SetRelativePosition(const glm::vec3 newPos)
{
	m_RelativePosition = newPos;
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

	glm::vec3 parentWorldPosition = m_pOwner->GetTransform()->GetWorldPosition();
	m_RelativePosition = parentWorldPosition - m_WorldPosition;
}

void TransformComponent::SetOwner(dae::SceneObject *pOwner)
{
	m_pOwner = pOwner;
}


