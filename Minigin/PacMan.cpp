#include "MiniginPCH.h"
#include "PacMan.h"
#include "InputManager.h"

PacMan::PacMan()
	:m_ControllerIdx{ 0 }, m_State{PacmanState::idle}
{
	Initialize();
}
PacMan::~PacMan()
{
	
}
void PacMan::Initialize()
{
	auto &inputManager = InputManager::GetInstance();
	inputManager.AddInput("MoveLeft", std::shared_ptr<Input>(std::make_shared<Input>(Input::PressedState::ButtonDown, XINPUT_GAMEPAD_DPAD_LEFT)));
	inputManager.AddInput("MoveRight", std::shared_ptr<Input>(std::make_shared<Input>(Input::PressedState::ButtonDown, XINPUT_GAMEPAD_DPAD_RIGHT)));
	inputManager.AddInput("MoveUp", std::shared_ptr<Input>(std::make_shared<Input>(Input::PressedState::ButtonDown, XINPUT_GAMEPAD_DPAD_UP)));
	inputManager.AddInput("MoveDown", std::shared_ptr<Input>(std::make_shared<Input>(Input::PressedState::ButtonDown, XINPUT_GAMEPAD_DPAD_DOWN)));
}
void PacMan::ProcessInput()
{
	auto &inputManager = InputManager::GetInstance();
	switch (m_State)
	{
	case PacmanState::idle:
		if (inputManager.IsInputTriggered(m_ControllerIdx, "MoveLeft"))
		{
			m_State = PacmanState::move;
			break;
		}
		if (inputManager.IsInputTriggered(m_ControllerIdx, "MoveRight"))
		{
			m_State = PacmanState::move;
			break;
		}
		if (inputManager.IsInputTriggered(m_ControllerIdx, "MoveLUp"))
		{
			m_State = PacmanState::move;
			break;
		}
		if (inputManager.IsInputTriggered(m_ControllerIdx, "MoveDown"))
		{
			m_State = PacmanState::move;
			break;
		}

		break;
	case PacmanState::move:
		if (inputManager.IsInputTriggered(m_ControllerIdx, "MoveLeft"))
		{
			break;
		}
		if (inputManager.IsInputTriggered(m_ControllerIdx, "MoveRight"))
		{
			break;
		}
		if (inputManager.IsInputTriggered(m_ControllerIdx, "MoveLUp"))
		{
			break;
		}
		if (inputManager.IsInputTriggered(m_ControllerIdx, "MoveDown"))
		{
			break;
		}
		m_State = PacmanState::idle;
		break;
	case PacmanState::supermove:
		break;
	case PacmanState::dead:
		break;
	}
}