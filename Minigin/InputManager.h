#pragma once
#include "Singleton.h"
#include "Controller.h"
#include <map>
#include <vector>
#include "BaseCommand.h"


class InputManager : public dae::Singleton<InputManager>
{
public:
	InputManager();
	bool ProcessInput();
	std::shared_ptr<Command> GetCommand(int controllerId) const;
	
	//Command Setting
	void SetGamepadUpCommand(int controllerId, std::shared_ptr<Command> pConcreteCommand);
	void SetGamepadDownCommand(int controllerId, std::shared_ptr<Command> pConcreteCommand);
	void SetGamepadLeftCommand(int controllerId, std::shared_ptr<Command> pConcreteCommand);
	void SetGamepadRightCommand(int controllerId, std::shared_ptr<Command> pConcreteCommand);
private:
	//Commands

	std::vector<Controller> m_Controllers;
};

