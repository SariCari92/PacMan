#include "MiniginPCH.h"
#include "InputComponent.h"

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

void InputComponent::SetControllerId(int idx)
{
	m_pControllerId = idx;
}