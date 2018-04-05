#include "MiniginPCH.h"
#include  "TransformComponent.h"

TransformComponent::TransformComponent()
	:m_Position{}
{

}
TransformComponent::~TransformComponent()
{

}

void TransformComponent::SetPosition(const Float3 newPos)
{
	m_Position = newPos;
}
Float3 TransformComponent::GetPosition() const
{
	return m_Position;
}

void TransformComponent::Translate(float x, float y, float z)
{
	m_Position.x += x;
	m_Position.y += y;
	m_Position.z += z;
}
