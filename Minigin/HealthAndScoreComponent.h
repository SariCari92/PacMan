#pragma once
#include "ComponentBase.h"

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
private:
	int m_Score;
	int m_Lives;
};
