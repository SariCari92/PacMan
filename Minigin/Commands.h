#pragma once
#include "BaseCommand.h"

namespace dae
{
	class SceneObject;
}

class IgnoreCommand final : public Command
{
	void Execute(dae::SceneObject *pObject, float deltaTime) override;
};

class MoveUpCommand final : public Command
{
	void Execute(dae::SceneObject *pObject, float deltaTime) override;
};
class MoveDownCommand final : public Command
{
	void Execute(dae::SceneObject *pObject, float deltaTime) override;
};
class MoveLeftCommand final : public Command
{
	void Execute(dae::SceneObject *pObject, float deltaTime) override;
};
class MoveRightCommand final : public Command
{
	void Execute(dae::SceneObject *pObject, float deltaTime) override;
};
class SelectCommand final : public Command
{
	void Execute(dae::SceneObject *pObject, float deltaTime) override {};
};
