#pragma once
#include "InputComponent.h"

class InputComponentPacMan : public InputComponent
{
public:
	InputComponentPacMan();
	InputComponentPacMan(int controllerId);
	~InputComponentPacMan();
	void LateUpdate(float deltaTime, std::shared_ptr<Command> controllerCommand) override;
private:
	void InitializeCommandConfiguration();
};


