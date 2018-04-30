#pragma once
#include "ComponentBase.h"
#include "InputManager.h"

class Command;

class InputComponent : public ComponentBase
{
public:
	InputComponent();
	InputComponent(int idx);
	~InputComponent();

	void Update(float deltaTime) override;
	void Render() const override;
	void SetControllerId(int idx);
private:
	std::shared_ptr<Command> GetCommand() const;
	int m_pControllerId;
};