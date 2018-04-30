#include "MiniginPCH.h"
#include "InputComponent.h"
#include "InputManager.h"
#include "Command.h"

InputComponent::InputComponent()
{

}
InputComponent::InputComponent(int idx)
	:m_pControllerId{idx}
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
}

void InputComponent::Render() const
{

}

void InputComponent::SetControllerId(int idx)
{
	m_pControllerId = idx;
}

std::shared_ptr<Command> InputComponent::GetCommand() const
{
	return InputManager::GetInstance().GetCommand(m_pControllerId);
}