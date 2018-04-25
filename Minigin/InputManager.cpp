#include "MiniginPCH.h"
#include "InputManager.h"
#include <iostream>
#include <SDL.h>

InputManager::InputManager()
	:m_Controllers{}, m_Inputs{}
{
	for (int idx{ 0 }; idx < 4; ++idx)
	{
		m_Controllers.push_back(Controller(idx));
	}
}

bool InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			return false;
		}
	}

	for (Controller &controller : m_Controllers)
	{
		controller.Update();
	}

	return true;
}

void InputManager::AddInput(const std::string &inputName, const std::shared_ptr<Input> input)
{
	m_Inputs[inputName] = input;
}

bool InputManager::IsInputTriggered(int ControllerId, std::string inputName)
{
	if (m_Controllers[ControllerId].GetXInputState().Gamepad.wButtons & m_Inputs[inputName]->pressedButton)
	{
		return true;
	}

	return false;
}