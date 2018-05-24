#include "MiniginPCH.h"
#include "MovementComponent.h"
#include "SceneObject.h"
#include "Helper.h"
#include "Renderer.h"

MovementComponent::MovementComponent()
	:m_Speed{ 150.0f }, m_MovementState{ MovementState::idle }, m_IsDebugRender{true}
{

}

MovementComponent::~MovementComponent()
{

}

void MovementComponent::Update(float deltaTime)
{
	std::shared_ptr<TransformComponent> pTransformComp = m_pOwner->GetTransform();
	glm::vec3 ownerPos = pTransformComp->GetWorldPosition();
	switch (m_MovementState)
	{
	case MovementState::up:
	{
		SDL_Rect tempCollBox = m_CollisionBox;
		tempCollBox.y += int(-deltaTime * m_Speed) - 2;
		bool hasCollision{ false };
		for (std::weak_ptr<Grid> pGrid : m_pCurrentGrid->adjGrids)
		{
			if (SDL_HasIntersection(&tempCollBox, &pGrid.lock()->rect) && pGrid.lock()->isObstacle)
			{
				std::cout << "TOP COLLISION" << std::endl;
				hasCollision = true;
				m_CollisionBox.y = m_pCurrentGrid->rect.y;
				break;
			}
		}

		if (hasCollision) break;

		pTransformComp->Translate(0.0f, -deltaTime * m_Speed, 0.0f);
		m_CollisionBox.y = (int)ownerPos.y;
		if (ownerPos.y < m_pCurrentGrid->adjGrids[1].lock()->rect.y)
		{
			m_pCurrentGrid = m_pCurrentGrid->adjGrids[1].lock();
			m_CollisionBox.y = m_pCurrentGrid->rect.y;
			pTransformComp->SetWorldPosition(glm::vec3(ownerPos.x, m_CollisionBox.y, ownerPos.z));
		}
		
		break;
	}
	case MovementState::down:
	{
		SDL_Rect tempCollBox = m_CollisionBox;
		tempCollBox.y += int(deltaTime * m_Speed) + 2;
		bool hasCollision{ false };
		for (std::weak_ptr<Grid> pGrid : m_pCurrentGrid->adjGrids)
		{
			if (SDL_HasIntersection(&tempCollBox, &pGrid.lock()->rect) && pGrid.lock()->isObstacle)
			{
				std::cout << "BOTTOM COLLISION" << std::endl;
				hasCollision = true;
				m_CollisionBox.y = m_pCurrentGrid->rect.y;
				break;
			}
		}

		if (hasCollision) break;

		pTransformComp->Translate(0.0f, deltaTime * m_Speed, 0.0f);
		m_CollisionBox.y = (int)ownerPos.y;
		if (ownerPos.y > m_pCurrentGrid->adjGrids[7].lock()->rect.y)
		{
			m_pCurrentGrid = m_pCurrentGrid->adjGrids[7].lock();
			m_CollisionBox.y = m_pCurrentGrid->rect.y;
			pTransformComp->SetWorldPosition(glm::vec3(ownerPos.x, m_CollisionBox.y, ownerPos.z));
		}
		break;
	}
	case MovementState::left:
	{
		SDL_Rect tempCollBox = m_CollisionBox;
		tempCollBox.x += int(-deltaTime * m_Speed) - 2;
		bool hasCollision{ false };
		for (std::weak_ptr<Grid> pGrid : m_pCurrentGrid->adjGrids)
		{
			if (SDL_HasIntersection(&tempCollBox, &pGrid.lock()->rect) && pGrid.lock()->isObstacle)
			{
				std::cout << "LEFT COLLISION" << std::endl;
				hasCollision = true;
				m_CollisionBox.x = m_pCurrentGrid->rect.x;
				break;
			}
		}

		if (hasCollision) break;

		pTransformComp->Translate(-deltaTime * m_Speed, 0.0f, 0.0f);
		m_CollisionBox.x = (int)ownerPos.x;
		if (ownerPos.x < m_pCurrentGrid->adjGrids[3].lock()->rect.x)
		{
			m_pCurrentGrid = m_pCurrentGrid->adjGrids[3].lock();
			m_CollisionBox.x = m_pCurrentGrid->rect.x;
			pTransformComp->SetWorldPosition(glm::vec3(m_CollisionBox.x, ownerPos.y, ownerPos.z));
		}
		break;
	}
	case MovementState::right:
	{
		SDL_Rect tempCollBox = m_CollisionBox;
		tempCollBox.x += int(deltaTime * m_Speed) + 2;
		bool hasCollision{ false };
		for (std::weak_ptr<Grid> pGrid : m_pCurrentGrid->adjGrids)
		{
			if (SDL_HasIntersection(&tempCollBox, &pGrid.lock()->rect) && pGrid.lock()->isObstacle)
			{
				std::cout << "RIGHT COLLISION" << std::endl;
				hasCollision = true;
				m_CollisionBox.x = m_pCurrentGrid->rect.x;
				break;
			}
		}

		if (hasCollision) break;

		pTransformComp->Translate(deltaTime * m_Speed, 0.0f, 0.0f);
		m_CollisionBox.x = (int)ownerPos.x;
		if (ownerPos.x > m_pCurrentGrid->adjGrids[5].lock()->rect.x)
		{
			m_pCurrentGrid = m_pCurrentGrid->adjGrids[5].lock();
			m_CollisionBox.x = m_pCurrentGrid->rect.x;
			pTransformComp->SetWorldPosition(glm::vec3(m_CollisionBox.x, ownerPos.y, ownerPos.z));
		}
		break;
	}
	case MovementState::idle:
		break;
	}
}
void MovementComponent::Render() const
{
	if (m_IsDebugRender)
	{
		DrawRectangle(&m_CollisionBox, CreateSDLColor(255, 0, 0, 255));
		for (std::weak_ptr<Grid> pGrid : m_pCurrentGrid->adjGrids)
		{
			if (pGrid.lock())DrawRectangle(&pGrid.lock()->rect, CreateSDLColor(0, 255, 0, 255));
		}
	}
}

void MovementComponent::MoveUp(float deltaTime)
{
	SDL_Rect tempCollBox = m_CollisionBox;
	tempCollBox.y += int(-deltaTime * m_Speed) - 2;
	for (std::weak_ptr<Grid> pGrid : m_pCurrentGrid->adjGrids)
	{
		if (SDL_HasIntersection(&tempCollBox, &pGrid.lock()->rect) && pGrid.lock()->isObstacle)
		{
			std::cout << "TOP COLLISION" << std::endl;
			//m_CollisionBox.y = m_pCurrentGrid->rect.y;
			return;
		}
	}
	m_MovementState = MovementState::up;
}
void MovementComponent::MoveDown(float deltaTime)
{
	SDL_Rect tempCollBox = m_CollisionBox;
	tempCollBox.y += int(deltaTime * m_Speed) + 2;
	for (std::weak_ptr<Grid> pGrid : m_pCurrentGrid->adjGrids)
	{
		if (SDL_HasIntersection(&tempCollBox, &pGrid.lock()->rect) && pGrid.lock()->isObstacle)
		{
			std::cout << "BOTTOM COLLISION" << std::endl;
			//m_CollisionBox.y = m_pCurrentGrid->rect.y;
			return;
		}
	}
	m_MovementState = MovementState::down;
}
void MovementComponent::MoveLeft(float deltaTime)
{
	SDL_Rect tempCollBox = m_CollisionBox;
	tempCollBox.x += int(-deltaTime * m_Speed) - 2;
	for (std::weak_ptr<Grid> pGrid : m_pCurrentGrid->adjGrids)
	{
		if (SDL_HasIntersection(&tempCollBox, &pGrid.lock()->rect) && pGrid.lock()->isObstacle)
		{
			std::cout << "LEFT COLLISION" << std::endl;
			//m_CollisionBox.x = m_pCurrentGrid->rect.x;
			return;
		}
	}
	m_MovementState = MovementState::left;
}
void MovementComponent::MoveRight(float deltaTime)
{
	SDL_Rect tempCollBox = m_CollisionBox;
	tempCollBox.x += int(deltaTime * m_Speed) + 2;
	for (std::weak_ptr<Grid> pGrid : m_pCurrentGrid->adjGrids)
	{
		if (SDL_HasIntersection(&tempCollBox, &pGrid.lock()->rect) && pGrid.lock()->isObstacle)
		{
			std::cout << "RIGHT COLLISION" << std::endl;
			//m_CollisionBox.x = m_pCurrentGrid->rect.x;
			return;
		}
	}
	m_MovementState = MovementState::right;
}
void MovementComponent::SetCurrentGrid(std::shared_ptr<Grid> pGrid)
{
	m_pCurrentGrid = pGrid;
	m_CollisionBox = pGrid->rect;
}

std::shared_ptr<Grid> MovementComponent::GetCurrentGrid() const
{
	return m_pCurrentGrid;
}

const SDL_Rect& MovementComponent::GetCollisionBox() const
{
	return m_CollisionBox;
}

void MovementComponent::SetCollisionBox(SDL_Rect& box)
{
	m_CollisionBox = box;
}

void MovementComponent::SetMovementState(MovementState state)
{
	m_MovementState = state;
}