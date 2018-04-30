#include "MiniginPCH.h"
#include "Command.h"

void IgnoreCommand::Execute(SceneObject *pObject, float deltaTime)
{
	
}

void MoveUpCommand::Execute(SceneObject *pObject, float deltaTime)
{
	//pObject->GetTransform()->Translate(1.0f * deltaTime, 0.0f, 0.0f);
	std::cout << "MoveUp is Pressed" << std::endl;
}

void MoveDownCommand::Execute(SceneObject *pObject, float deltaTime)
{
	std::cout << "MoveDown is Pressed" << std::endl;
}

void MoveLeftCommand::Execute(SceneObject *pObject, float deltaTime)
{
	std::cout << "MoveLeft is Pressed" << std::endl;
}

void MoveRightCommand::Execute(SceneObject *pObject, float deltaTime)
{
	std::cout << "MoveRight is Pressed" << std::endl;
}
