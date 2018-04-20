#pragma once
#include<Windows.h>
#include<Xinput.h>
#include<chrono>

#pragma comment(lib, "XInput.lib")

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
	int m_ControllerID;
	bool m_IsActive;
	XINPUT_STATE m_InputState;
};
