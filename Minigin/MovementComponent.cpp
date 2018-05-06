#include "MiniginPCH.h"
#include "MovementComponent.h"
#include "SceneObject.h"

MovementComponent::MovementComponent()
	:m_Speed{100.0f}, m_MovementState{MovementState::idle}
{

}

MovementComponent::~MovementComponent()
{

}

void MovementComponent::Update(float deltaTime)
{
	switch (m_MovementState)
	{
	case MovementState::up:
		m_pOwner->GetTransform()->Translate(0.0f, -m_Speed * deltaTime, 0.0f);
		break;
	case MovementState::down:
		m_pOwner->GetTransform()->Translate(0.0f, m_Speed * deltaTime, 0.0f);
		break;
	case MovementState::left:
		m_pOwner->GetTransform()->Translate(-m_Speed * deltaTime, 0.0f, 0.0f);
		break;
	case MovementState::right:
		m_pOwner->GetTransform()->Translate(m_Speed * deltaTime, 0.0f, 0.0f);
		break;
	default:
		break;
	}
}
void MovementComponent::Render() const
{
	
}

void MovementComponent::MoveUp(float deltaTime)
{
	m_MovementState = MovementState::up;
}
void MovementComponent::MoveDown(float deltaTime)
{
	m_MovementState = MovementState::down;
}
void MovementComponent::MoveLeft(float deltaTime)
{
	m_MovementState = MovementState::left;
}
void MovementComponent::MoveRight(float deltaTime)
{
	m_MovementState = MovementState::right;
}