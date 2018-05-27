#include "MiniginPCH.h"
#include "TextComponent.h"
#include "Font.h"
#include "Renderer.h"
#include "SceneObject.h"
#include "glm\vec4.hpp"

TextComponent::TextComponent()
{

}
TextComponent::TextComponent(const std::string& text, std::shared_ptr<Font> font)
	:m_Text{ text }, m_Font{ font }, m_TexturePivot{}, m_TextureWorldPosition{}
{

}
TextComponent::~TextComponent()
{
	std::cout << "TextComponent Destructor Called!" << std::endl;
}

void TextComponent::Update(float deltaTime)
{
	if (m_pOwner) m_TextureWorldPosition = m_pOwner->GetTransform()->GetWorldPosition() + m_TexturePivot;

	if (m_NeedsUpdate)
	{
		//const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const SDL_Color color = { (Uint8)m_TextColor.r, (Uint8)m_TextColor.g , (Uint8)m_TextColor.b , (Uint8)m_TextColor.a };
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_Texture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}

	

}
void TextComponent::Render() const
{
	if (m_Texture != nullptr)
	{
		Renderer::GetInstance().RenderTexture(*m_Texture, m_TextureWorldPosition.x, m_TextureWorldPosition.y);
	}
}
void TextComponent::SetText(const std::string& text)
{
	m_Text = text;
}
const std::shared_ptr<Texture2D>& TextComponent::GetTexture() const
{
	return m_Texture;
}

void TextComponent::SetPivot(glm::vec3 newPivot)
{
	m_TexturePivot = newPivot;
}

void TextComponent::SetTextColor(glm::vec4 color)
{
	m_TextColor = color;
	m_NeedsUpdate = true;
}
