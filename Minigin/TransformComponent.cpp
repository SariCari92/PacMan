#include "MiniginPCH.h"
#include  "TransformComponent.h"
#include "SceneObject.h"

TransformComponent::TransformComponent()
	: m_RelativePosition{}
	, m_WorldPosition{}
	, m_pOwner{nullptr}
{

}

TransformComponent::~TransformComponent()
{

}

void TransformComponent::SetWorldPosition(const Float3 newPos)
{
	m_WorldPosition = newPos;
}
Float3 TransformComponent::GetWorldPosition() const
{
	return m_WorldPosition;
}
void TransformComponent::SetRelativePosition(const Float3 newPos)
{
	m_RelativePosition = newPos;
}
Float3 TransformComponent::GetRelativePosition() const
{
	return m_RelativePosition;
}

void TransformComponent::Translate(float x, float y, float z)
{
	m_WorldPosition.x += x;
	m_WorldPosition.y += y;
	m_WorldPosition.z += z;

	std::vector<std::shared_ptr<SceneObject>> children = m_pOwner->GetChildren();
	for (auto child : children)
	{
		child->GetTransform()->Translate(x, y, z);
	}

	Float3 parentWorldPosition = m_pOwner->GetTransform()->GetWorldPosition();
	m_RelativePosition = parentWorldPosition - m_WorldPosition;
}

void TransformComponent::SetOwner(std::unique_ptr<dae::SceneObject>& pOwner)
{
	m_pOwner = std::move(pOwner);
}
