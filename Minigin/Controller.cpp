#include "MiniginPCH.h"
#include "Controller.h"
#include "Commands.h"

Controller::Controller(int idx)
	:m_ControllerID{ idx }
	, m_pGamepadUp{nullptr}
	, m_pGamepadDown{ nullptr }
	, m_pGamepadLeft{ nullptr }
	, m_pGamepadRight{ nullptr }
	, m_pGamePadA{ nullptr }
{
	ZeroMemory(&m_InputState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_PrevInputState, sizeof(XINPUT_STATE));
}
Controller::~Controller()
{

}

void Controller::Update()
{
	m_PrevInputState = m_InputState;
	DWORD result{};
	result = XInputGetState(m_ControllerID, &m_InputState);
	result == ERROR_SUCCESS ? m_IsActive = true : m_IsActive = false;
}

int Controller::GetControllerId() const
{
	return m_ControllerID;
}
bool Controller::GetIsActive() const
{
	return m_IsActive;
}
XINPUT_STATE Controller::GetXInputState() const
{
	return m_InputState;
}