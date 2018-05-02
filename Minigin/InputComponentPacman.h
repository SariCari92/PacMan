#pragma once
#include "InputComponent.h"

class InputComponentPacMan : public InputComponent
{
public:
	InputComponentPacMan();
	InputComponentPacMan(int controllerId);
	~InputComponentPacMan();
	void Update(float deltaTime) override;
private:
	void InitializeCommandConfiguration();
};


