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

std::shared_ptr<Command> InputManager::GetCommand(int controllerId, PressState state) const
{
	const Controller &controller{ m_Controllers[controllerId] };

	switch (state)
	{
	case InputManager::PressState::Down:
		if ((controller.m_InputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
			&& !(controller.m_PrevInputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP))
			return controller.m_pGamepadUp;
		if ((controller.m_InputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
			&& !(controller.m_PrevInputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN))
			return controller.m_pGamepadDown;
		if ((controller.m_InputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
			&& !(controller.m_PrevInputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT))
			return controller.m_pGamepadLeft;
		if ((controller.m_InputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
			&& !(controller.m_PrevInputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT))
			return controller.m_pGamepadRight;
		if ((controller.m_InputState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
			&& !(controller.m_PrevInputState.Gamepad.wButtons & XINPUT_GAMEPAD_A))
			return controller.m_pGamePadA;

		return nullptr;
		break;
	case InputManager::PressState::Up:
		return nullptr;
		break;
	case InputManager::PressState::Pressed:
		if (controller.GetXInputState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) return controller.m_pGamepadUp;
		if (controller.GetXInputState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) return controller.m_pGamepadDown;
		if (controller.GetXInputState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) return controller.m_pGamepadLeft;
		if (controller.GetXInputState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) return controller.m_pGamepadRight;
		if (controller.GetXInputState().Gamepad.wButtons & XINPUT_GAMEPAD_A) return controller.m_pGamePadA;

		return nullptr;
		break;
	}

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
void InputManager::SetGamepadACommand(int controllerId, std::shared_ptr<Command> pConcreteCommand)
{
	m_Controllers[controllerId].m_pGamePadA = pConcreteCommand;
}