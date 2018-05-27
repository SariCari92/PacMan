#pragma once
#include "ComponentBase.h"
#include "Texture2D.h"
#include <memory>
#include "Structs.h"
#include <glm\vec3.hpp>

using namespace dae;

class TextureComponent : public ComponentBase
{
public:
	TextureComponent();
	TextureComponent(std::string texture);
	~TextureComponent();

	void Update(float deltaTime) override;
	void Render() const override;

	void SetTexture(std::string texture);
	const std::shared_ptr<Texture2D> GetTexture() const;
	void SetPivot(glm::vec3 newPivot);
private:
	std::shared_ptr<Texture2D> m_pTexture;
	glm::vec3 m_TextureWorldPosition;
	glm::vec3 m_TexturePivot; //Position Relative to WorldPosition
};
