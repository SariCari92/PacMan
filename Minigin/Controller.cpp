#include "MiniginPCH.h"
#include "Controller.h"
#include "Command.h"

Controller::Controller(int idx)
	:m_ControllerID{ idx }
	, m_pGamepadUp{new MoveUpCommand()}
	, m_pGamepadDown{new MoveDownCommand()}
	, m_pGamepadLeft{new MoveLeftCommand()}
	, m_pGamepadRight{new MoveRightCommand()}
{
	ZeroMemory(&m_InputState, sizeof(XINPUT_STATE));
}
Controller::~Controller()
{

}

void Controller::Update()
{
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