#pragma once
#include "ComponentBase.h"
#include "InputManager.h"

class InputComponent : public ComponentBase
{
public:
	InputComponent();
	InputComponent(int idx);
	~InputComponent();

	void Update() = 0;
	void SetControllerId(int idx);
private:
	int m_pControllerId;
};