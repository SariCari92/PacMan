#include "MiniginPCH.h"
#include "InputComponentPacman.h"
#include "InputManager.h"
#include "Commands.h"
#include "MovementComponent.h"

InputComponentPacMan::InputComponentPacMan()
{

}
InputComponentPacMan::InputComponentPacMan(int controllerId)
	:InputComponent(controllerId)
{
	InitializeCommandConfiguration();
}
InputComponentPacMan::~InputComponentPacMan()
{

}
void InputComponentPacMan::LateUpdate(float deltaTime, std::shared_ptr<Command> controllerCommand)
{
	//if Controller Command is null, then don't executed keyboard command; to avoid double executing of movecommand
	if (!controllerCommand)
	{
		switch (m_ControllerId)
		{
		case 0:
		{
			if (GetAsyncKeyState(VK_LEFT) & 0x8000)
			{
				std::shared_ptr<Command> command = std::make_shared<MoveLeftCommand>();
				command->Execute(m_pOwner, deltaTime);
			}
			if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
			{
				std::shared_ptr<Command> command = std::make_shared<MoveRightCommand>();
				command->Execute(m_pOwner, deltaTime);
			}
			if (GetAsyncKeyState(VK_UP) & 0x8000)
			{
				std::shared_ptr<Command> command = std::make_shared<MoveUpCommand>();
				command->Execute(m_pOwner, deltaTime);
			}
			if (GetAsyncKeyState(VK_DOWN) & 0x8000)
			{
				std::shared_ptr<Command> command = std::make_shared<MoveDownCommand>();
				command->Execute(m_pOwner, deltaTime);
			}
			break;
		}
		case 1:
		{
			if (GetAsyncKeyState(0x41))
			{
				std::shared_ptr<Command> command = std::make_shared<MoveLeftCommand>();
				command->Execute(m_pOwner, deltaTime);
			}
			if (GetAsyncKeyState(0x44))
			{
				std::shared_ptr<Command> command = std::make_shared<MoveRightCommand>();
				command->Execute(m_pOwner, deltaTime);
			}
			if (GetAsyncKeyState(0x57))
			{
				std::shared_ptr<Command> command = std::make_shared<MoveUpCommand>();
				command->Execute(m_pOwner, deltaTime);
			}
			if (GetAsyncKeyState(0x53))
			{
				std::shared_ptr<Command> command = std::make_shared<MoveDownCommand>();
				command->Execute(m_pOwner, deltaTime);
			}
			break;
		}
		}
	}
}
void InputComponentPacMan::InitializeCommandConfiguration()
{
	InputManager &inputManager = InputManager::GetInstance();
	inputManager.SetGamepadUpCommand(m_ControllerId, std::shared_ptr<Command>(new MoveUpCommand()));
	inputManager.SetGamepadDownCommand(m_ControllerId, std::shared_ptr<Command>(new MoveDownCommand()));
	inputManager.SetGamepadLeftCommand(m_ControllerId, std::shared_ptr<Command>(new MoveLeftCommand()));
	inputManager.SetGamepadRightCommand(m_ControllerId, std::shared_ptr<Command>(new MoveRightCommand()));
}