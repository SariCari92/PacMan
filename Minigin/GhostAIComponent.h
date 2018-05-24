#pragma once
#include "ComponentBase.h"

class GhostAIComponent : public ComponentBase
{
public:
	GhostAIComponent();
	~GhostAIComponent();

	void Update(float deltaTime) override;
	void Render() const override;
private:
	float m_UpdateTimer;
	float m_TimerTimeLeft;
};
