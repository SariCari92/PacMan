#pragma once
#include "Singleton.h"
#include "Controller.h"
#include <map>
#include <vector>
#include "Command.h"

struct Input
{
	enum class PressedState
	{
		ButtonPressed,
		ButtonReleased,
		ButtonDown
	};

	Input();
	Input(PressedState state, int pressedButton);

	PressedState pressedState;
	int pressedButton;
};

class InputManager : public dae::Singleton<InputManager>
{
public:
	InputManager();

	bool ProcessInput();
	void AddInput(const std::string &inputName, const std::shared_ptr<Input> input);
	bool IsInputTriggered(int ControllerId, std::string inputName);
	std::shared_ptr<Command> GetCommand(int controllerId) const;

private:
	//Commands
	std::shared_ptr<Command> m_pGamepadUp;
	std::shared_ptr<Command> m_pGamepadDown;
	std::shared_ptr<Command> m_pGamepadLeft;
	std::shared_ptr<Command> m_pGamepadRight;

	std::vector<Controller> m_Controllers;
	std::map<std::string, std::shared_ptr<Input>> m_Inputs;
};

