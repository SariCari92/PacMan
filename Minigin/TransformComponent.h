#pragma once
#include "ComponentBase.h"
#include "Structs.h"
#include <glm\vec3.hpp>

namespace dae
{
	class SceneObject;
}

class TransformComponent final
{
public:
	TransformComponent();
	~TransformComponent();

	void SetWorldPosition(const glm::vec3 newPos);
	glm::vec3 GetWorldPosition() const;
	void SetRelativePosition(const glm::vec3 newPos);
	glm::vec3 GetRelativePosition() const;
	void Translate(float x, float y, float z);
	void Translate(glm::vec3 translation);
	void SetOwner(dae::SceneObject *pOwner);
private:

	glm::vec3 m_RelativePosition;
	glm::vec3 m_WorldPosition;

	dae::SceneObject *m_pOwner;
};
