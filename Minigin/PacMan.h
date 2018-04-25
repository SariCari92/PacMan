#pragma once
#include "SceneObject.h"

class PacMan final : public SceneObject
{
public:
	PacMan();
	~PacMan();
private:
	void Initialize();
	void ProcessInput();
public:
	enum class PacmanState
	{
		idle,
		move,
		supermove,
		dead
	};
private:
	int m_ControllerIdx;
	PacmanState m_State;
};