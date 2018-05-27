#pragma once
#include "SceneObject.h"

using namespace dae;

class Command
{
public:
	Command() = default;
	~Command() = default;

	virtual void Execute(SceneObject *pObject, float deltaTime) = 0;
};


