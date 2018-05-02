#include "MiniginPCH.h"
#include "InputManager.h"
#include <iostream>
#include <SDL.h>


InputManager::InputManager()
	:m_Controllers{}
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


std::shared_ptr<Command> InputManager::GetCommand(int controllerId) const
{
	const Controller &controller{ m_Controllers[controllerId] };
	if (controller.GetXInputState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) return controller.m_pGamepadUp;
	if (controller.GetXInputState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) return controller.m_pGamepadDown;
	if (controller.GetXInputState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) return controller.m_pGamepadLeft;
	if (controller.GetXInputState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) return controller.m_pGamepadRight;

	return nullptr;
}

void InputManager::SetGamepadUpCommand(int controllerId, std::shared_ptr<Command> pConcreteCommand)
{
	m_Controllers[controllerId].m_pGamepadUp = pConcreteCommand;
}
void InputManager::SetGamepadDownCommand(int controllerId, std::shared_ptr<Command> pConcreteCommand)
{
	m_Controllers[controllerId].m_pGamepadDown = pConcreteCommand;
}
void InputManager::SetGamepadLeftCommand(int controllerId, std::shared_ptr<Command> pConcreteCommand)
{
	m_Controllers[controllerId].m_pGamepadLeft = pConcreteCommand;
}
void InputManager::SetGamepadRightCommand(int controllerId, std::shared_ptr<Command> pConcreteCommand)
{
	m_Controllers[controllerId].m_pGamepadRight = pConcreteCommand;
}