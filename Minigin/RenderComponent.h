#pragma once
#include "ComponentBase.h"
#include "TextComponent.h"
#include "TextureComponent.h"

class RenderComponent : public ComponentBase
{
public:
	RenderComponent();
	~RenderComponent();

	void Update() override;
	void Render();
};
