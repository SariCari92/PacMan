#pragma once
#include "ComponentBase.h"
#include "Transform.h"
#include "Font.h"
#include "Texture2D.h"
#include "Structs.h"
#include "glm\vec4.hpp"

using namespace dae;

class TextComponent final : public ComponentBase
{
public:
	TextComponent();
	TextComponent(const std::string& text, std::shared_ptr<Font> font);
	~TextComponent();

	void Update(float deltaTime) override;
	void Render() const override;
	void SetText(const std::string& text);
	void SetPivot(glm::vec3 newPivot);
	void SetTextColor(glm::vec4 color);

	const std::shared_ptr<Texture2D>& GetTexture() const;

private:
	bool m_NeedsUpdate;
	std::string m_Text;
	glm::vec3 m_TextureWorldPosition;
	glm::vec3 m_TexturePivot;
	std::shared_ptr<Font> m_Font;
	std::shared_ptr<Texture2D> m_Texture;
	glm::vec4 m_TextColor;
};
