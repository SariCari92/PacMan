#pragma once
#include "ComponentBase.h"
#include <SDL_rect.h>
#include <glm\vec3.hpp>

class PhysicsComponent final : public ComponentBase
{
public:
	PhysicsComponent();
	~PhysicsComponent();

	void Update(float deltaTime) override;
	void Render() const override;
	void SetCollisionBox(const SDL_Rect &rect);
	void SetPivot(glm::vec3 newPivot);
private:
	SDL_Rect m_CollisionBox;
	bool m_IsRenderActive;
	glm::vec3 m_WorldPosition;
	glm::vec3 m_Pivot;
};

