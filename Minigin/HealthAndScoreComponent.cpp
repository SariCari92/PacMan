#include "MiniginPCH.h"
#include "HealthAndScoreComponent.h"
#include "SceneObject.h"
#include "MovementComponent.h"

HealthAndScoreComponent::HealthAndScoreComponent()
	:m_Score{0}, m_Lives{3}
{

}
HealthAndScoreComponent::~HealthAndScoreComponent()
{

}

void HealthAndScoreComponent::Update(float deltaTime)
{
	for (int gridIdx{ 0 }; gridIdx < 9; ++gridIdx)
	{
		if (SDL_HasIntersection(m_pOwner->GetComponent<MovementComponent>()->GetCurrentGrid()->adjGrids[gridIdx].lock()->point.get(), &m_pOwner->GetComponent<MovementComponent>()->GetCollisionBox()))
		{
			m_pOwner->GetComponent<MovementComponent>()->GetCurrentGrid()->adjGrids[gridIdx].lock()->point.reset();
			m_Score++;
		}
		if (SDL_HasIntersection(m_pOwner->GetComponent<MovementComponent>()->GetCurrentGrid()->adjGrids[gridIdx].lock()->specialPoint.get(), &m_pOwner->GetComponent<MovementComponent>()->GetCollisionBox()))
		{
			m_pOwner->GetComponent<MovementComponent>()->GetCurrentGrid()->adjGrids[gridIdx].lock()->specialPoint.reset();
			m_Score += 3;
		}
	}
}
void HealthAndScoreComponent::Render() const
{

}
void HealthAndScoreComponent::IncrementScore(int scoreToAdd)
{
	m_Score += scoreToAdd;
}
int HealthAndScoreComponent::GetScore() const
{
	return m_Score;
}
void HealthAndScoreComponent::DecrementLives()
{
	--m_Lives;
}
int HealthAndScoreComponent::GetLives() const
{
	return m_Lives;
}