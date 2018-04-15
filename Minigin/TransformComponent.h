#pragma once
#include "ComponentBase.h"
#include "Structs.h"

namespace dae
{
	class SceneObject;
}

class TransformComponent final
{
public:
	TransformComponent();
	~TransformComponent();

	void SetWorldPosition(const Float3 newPos);
	Float3 GetWorldPosition() const;
	void SetRelativePosition(const Float3 newPos);
	Float3 GetRelativePosition() const;
	void Translate(float x, float y, float z);
	void SetOwner(std::unique_ptr<dae::SceneObject>& pOwner);
private:
	Float3 m_RelativePosition;
	Float3 m_WorldPosition;
	std::unique_ptr<dae::SceneObject> m_pOwner;
};
