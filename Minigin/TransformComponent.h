#pragma once
#include "ComponentBase.h"
#include "Structs.h"

class TransformComponent final
{
public:
	TransformComponent();
	~TransformComponent();

	void SetPosition(const Float3 newPos);
	Float3 GetPosition() const;
	void Translate(float x, float y, float z);
private:
	Float3 m_Position;
};
