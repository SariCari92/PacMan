#include "MiniginPCH.h"
#include "InputComponent.h"
#include "InputManager.h"
#include "BaseCommand.h"
#include "Commands.h"

InputComponent::InputComponent()
{

}
InputComponent::InputComponent(int controllerId)
	:m_ControllerId{ controllerId }
{

}

InputComponent::~InputComponent()
{

}

void InputComponent::Update(float deltaTime)
{
	std::shared_ptr<Command> command = GetCommand();

	if (command)
	{
		command->Execute(m_pOwner, deltaTime);
	}

	LateUpdate(deltaTime, command);
}

void InputComponent::Render() const
{

}

void InputComponent::SetControllerId(int idx)
{
	m_ControllerId = idx;
}

std::shared_ptr<Command> InputComponent::GetCommand() const
{
	return InputManager::GetInstance().GetCommand(m_ControllerId);
}