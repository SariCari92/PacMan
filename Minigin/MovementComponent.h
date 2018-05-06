#pragma once
#include "ComponentBase.h"

class MovementComponent : public ComponentBase
{
public:
	MovementComponent();
	~MovementComponent();

	virtual void Update(float deltaTime) override;
	virtual void Render() const override;

	void MoveUp(float deltaTime);
	void MoveDown(float deltaTime);
	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);

	enum class MovementState
	{
		idle ,up, down, left, right
	};

private:
	float m_Speed;
	MovementState m_MovementState;
};
