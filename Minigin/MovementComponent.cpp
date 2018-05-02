#include "MiniginPCH.h"
#include "MovementComponent.h"
#include "SceneObject.h"

MovementComponent::MovementComponent()
	:m_Speed{100.0f}
{

}

MovementComponent::~MovementComponent()
{

}

void MovementComponent::Update(float deltaTime)
{

}
void MovementComponent::Render() const
{

}

void MovementComponent::MoveUp(float deltaTime)
{
	m_pOwner->GetTransform()->Translate(0.0f, -m_Speed * deltaTime, 0.0f);
}
void MovementComponent::MoveDown(float deltaTime)
{
	m_pOwner->GetTransform()->Translate(0.0f, m_Speed * deltaTime, 0.0f);
}
void MovementComponent::MoveLeft(float deltaTime)
{
	m_pOwner->GetTransform()->Translate(-m_Speed * deltaTime, 0.0f, 0.0f);
}
void MovementComponent::MoveRight(float deltaTime)
{
	m_pOwner->GetTransform()->Translate(m_Speed * deltaTime, 0.0f, 0.0f);
}