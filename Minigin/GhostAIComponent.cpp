#include "MiniginPCH.h"
#include "GhostAIComponent.h"
#include <random>
#include "SceneObject.h"
#include "Commands.h"

GhostAIComponent::GhostAIComponent()
	:m_UpdateTimer{ 1.5f }, m_TimerTimeLeft {m_UpdateTimer}
{

}

GhostAIComponent::~GhostAIComponent()
{

}

void GhostAIComponent::Update(float deltaTime)
{
	m_TimerTimeLeft -= deltaTime;
	if (m_TimerTimeLeft <= 0.0f)
	{
		m_TimerTimeLeft += m_UpdateTimer;
		int randNr = rand() % 4;
		std::shared_ptr<Command> command;
		switch (randNr)
		{
		case 0:
			command = std::make_shared<MoveUpCommand>();
			break;
		case 1:
			command = std::make_shared<MoveDownCommand>();
			break;
		case 2:
			command = std::make_shared<MoveLeftCommand>();
			break;
		case 3:
			command = std::make_shared<MoveRightCommand>();
			break;
		}
		command->Execute(m_pOwner, deltaTime);
	}
}
void GhostAIComponent::Render() const
{

}