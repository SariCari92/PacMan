#pragma once
#include "Singleton.h"
#include "Controller.h"
#include <map>
#include <vector>

struct Input
{
	enum class PressedState
	{
		ButtonPressed,
		ButtonReleased,
		ButtonDown
	};

	Input() = default;
	Input(PressedState state, WORD pressedButton)
		:pressedState{state}, pressedButton{ pressedButton }{}

	PressedState pressedState;
	WORD pressedButton;
};

class InputManager : public dae::Singleton<InputManager>
{
public:
	InputManager();

	bool ProcessInput();
	void AddInput(const std::string &inputName, const std::shared_ptr<Input> input);
	bool IsInputTriggered(int ControllerId, std::string inputName);

private:
	std::vector<Controller> m_Controllers;
	std::map<std::string, std::shared_ptr<Input>> m_Inputs;
};

