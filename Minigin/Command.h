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

class IgnoreCommand final : public Command
{
	void Execute(SceneObject *pObject, float deltaTime) override;
};

class MoveUpCommand final : public Command
{
	void Execute(SceneObject *pObject, float deltaTime) override;
};
class MoveDownCommand final : public Command
{
	void Execute(SceneObject *pObject, float deltaTime) override;
};
class MoveLeftCommand final : public Command
{
	void Execute(SceneObject *pObject, float deltaTime) override;
};
class MoveRightCommand final : public Command
{
	void Execute(SceneObject *pObject, float deltaTime) override;
};
