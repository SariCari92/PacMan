#include "MiniginPCH.h"
#include "PhysicsComponent.h"
#include <SDL_render.h>
#include "Renderer.h"
#include "SceneObject.h"

PhysicsComponent::PhysicsComponent()
	:m_IsRenderActive{true}
{

}
PhysicsComponent::~PhysicsComponent()
{

}

void PhysicsComponent::Update(float deltaTime)
{
	if (m_pOwner) m_WorldPosition = m_pOwner->GetTransform()->GetWorldPosition() + m_Pivot;
	m_CollisionBox.x = (int)m_WorldPosition.x;
	m_CollisionBox.y = (int)m_WorldPosition.y;
}
void PhysicsComponent::Render() const
{
	SDL_Renderer *pRenderer = dae::Renderer::GetInstance().GetSDLRenderer();
	SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 1);
	if (m_IsRenderActive)
		SDL_RenderDrawRect(pRenderer, &m_CollisionBox);
}

void PhysicsComponent::SetCollisionBox(const SDL_Rect &rect)
{
	m_CollisionBox = rect;
	m_Pivot.x = (float)rect.x;
	m_Pivot.y = (float)rect.y;
	m_Pivot.z = 0.0f;
}

void PhysicsComponent::SetPivot(glm::vec3 newPivot)
{

}