#pragma once
#include<Windows.h>
#include<Xinput.h>
#include<chrono>
#pragma comment(lib, "XInput.lib")

class Command;

class Controller
{
public:
	Controller(int idx);
	~Controller();
	void Update();

	int GetControllerId() const;
	bool GetIsActive() const;
	XINPUT_STATE GetXInputState() const;
private:
	friend class InputManager;
	int m_ControllerID;
	bool m_IsActive;
	XINPUT_STATE m_PrevInputState;
	XINPUT_STATE m_InputState;

	//Commands
	std::shared_ptr<Command> m_pGamepadUp;
	std::shared_ptr<Command> m_pGamepadDown;
	std::shared_ptr<Command> m_pGamepadLeft;
	std::shared_ptr<Command> m_pGamepadRight;
	std::shared_ptr<Command> m_pGamePadA;


};
