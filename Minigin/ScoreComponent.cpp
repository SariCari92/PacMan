#include "MiniginPCH.h"
#include "ScoreComponent.h"
#include "SceneObject.h"
#include "MovementComponent.h"

ScoreComponent::ScoreComponent()
	:m_Score{0}
{

}
ScoreComponent::~ScoreComponent()
{

}

void ScoreComponent::Update(float deltaTime)
{
	for (int gridIdx{ 0 }; gridIdx < 9; ++gridIdx)
	{
		if (SDL_HasIntersection(m_pOwner->GetComponent<MovementComponent>()->GetCurrentGrid()->adjGrids[gridIdx].lock()->point.get(), &m_pOwner->GetComponent<MovementComponent>()->GetCollisionBox()))
		{
			m_pOwner->GetComponent<MovementComponent>()->GetCurrentGrid()->adjGrids[gridIdx].lock()->point.reset();
			m_Score++;
		}
	}
}
void ScoreComponent::Render() const
{

}
void ScoreComponent::IncrementScore(int scoreToAdd)
{
	m_Score += scoreToAdd;
}
int ScoreComponent::GetScore() const
{
	return m_Score;
}