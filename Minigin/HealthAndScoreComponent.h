#pragma once
#include "ComponentBase.h"
#include "PacManGhostState.h"

class HealthAndScoreComponent final: public ComponentBase
{
public:
	HealthAndScoreComponent();
	~HealthAndScoreComponent();

	void Update(float deltaTime) override;
	void Render() const override;
	void IncrementScore(int scoreToAdd);
	int GetScore() const;
	void DecrementLives();
	int GetLives() const;
	bool GetIsSuperMode() const;
private:
	int m_Score;
	int m_Lives;
	bool m_IsSuperMode;
	float m_SuperModeTimer;
	float m_SuperModeTimerLeft;
};
