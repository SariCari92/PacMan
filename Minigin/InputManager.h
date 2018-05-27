#pragma once
#include "Singleton.h"
#include "Controller.h"
#include <vector>
#include "BaseCommand.h"

class InputManager : public dae::Singleton<InputManager>
{
public:
	enum class PressState
	{
		Down, 
		Up, 
		Pressed
	};

	InputManager();
	bool ProcessInput();
	std::shared_ptr<Command> GetCommand(int controllerId) const;
	std::shared_ptr<Command> GetCommand(int controllerId, PressState state) const;
	
	//Command Setting
	void SetGamepadUpCommand(int controllerId, std::shared_ptr<Command> pConcreteCommand);
	void SetGamepadDownCommand(int controllerId, std::shared_ptr<Command> pConcreteCommand);
	void SetGamepadLeftCommand(int controllerId, std::shared_ptr<Command> pConcreteCommand);
	void SetGamepadRightCommand(int controllerId, std::shared_ptr<Command> pConcreteCommand);
	void SetGamepadACommand(int controllerId, std::shared_ptr<Command> pConcreteCommand);
private:
	//Commands
	std::vector<Controller> m_Controllers;
};

