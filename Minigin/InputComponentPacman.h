#pragma once
#include "InputComponent.h"

class InputComponentPacMan : public InputComponent
{
public:
	InputComponentPacMan();
	InputComponentPacMan(int controllerId);
	~InputComponentPacMan();
	void LateUpdate() override;
private:
	void InitializeCommandConfiguration();
};


