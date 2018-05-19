#pragma once
#include "ComponentBase.h"

class ScoreComponent final: public ComponentBase
{
public:
	ScoreComponent();
	~ScoreComponent();

	void Update(float deltaTime) override;
	void Render() const override;
	void IncrementScore(int scoreToAdd);
	int GetScore() const;
private:
	int m_Score;

};
