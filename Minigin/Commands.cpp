#include "MiniginPCH.h"
#include "Commands.h"
#include "MovementComponent.h"

void IgnoreCommand::Execute(dae::SceneObject *pObject, float deltaTime)
{

}

void MoveUpCommand::Execute(dae::SceneObject *pObject, float deltaTime)
{
	std::shared_ptr<MovementComponent> movComp = pObject->GetComponent<MovementComponent>();
	if (movComp) movComp->MoveUp(deltaTime);
}

void MoveDownCommand::Execute(dae::SceneObject *pObject, float deltaTime)
{
	std::shared_ptr<MovementComponent> movComp = pObject->GetComponent<MovementComponent>();
	if (movComp) movComp->MoveDown(deltaTime);
}

void MoveLeftCommand::Execute(dae::SceneObject *pObject, float deltaTime)
{
	std::shared_ptr<MovementComponent> movComp = pObject->GetComponent<MovementComponent>();
	if (movComp) movComp->MoveLeft(deltaTime);
}

void MoveRightCommand::Execute(dae::SceneObject *pObject, float deltaTime)
{
	std::shared_ptr<MovementComponent> movComp = pObject->GetComponent<MovementComponent>();
	if (movComp) movComp->MoveRight(deltaTime);
}