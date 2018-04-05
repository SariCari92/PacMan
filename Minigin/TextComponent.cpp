#include "MiniginPCH.h"
#include "TextComponent.h"
#include "Font.h"
#include "Renderer.h"

TextComponent::TextComponent()
{

}
TextComponent::TextComponent(const std::string& text, std::shared_ptr<Font> font)
	:m_Text{text}, m_Font{font}
{

}
TextComponent::~TextComponent()
{

}

void TextComponent::Update() 
{
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
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
	}
}
void TextComponent::SetText(const std::string& text)
{
	m_Text = text;
}
void TextComponent::SetPosition(float x, float y)
{
	m_Position.x = x;
	m_Position.y = y;
}
Float3 TextComponent::GetPosition() const
{
	return m_Position;
}
const std::shared_ptr<Texture2D>& TextComponent::GetTexture() const
{
	return m_Texture;
}