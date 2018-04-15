#include "MiniginPCH.h"
#include "TextComponent.h"
#include "Font.h"
#include "Renderer.h"
#include "SceneObject.h"

TextComponent::TextComponent()
{

}
TextComponent::TextComponent(const std::string& text, std::shared_ptr<Font> font)
	:m_Text{ text }, m_Font{ font }, m_RelativePosition{}, m_WorldPosition{}
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

	if(m_pOwner) m_WorldPosition = m_pOwner->GetTransform()->GetWorldPosition() + m_RelativePosition;

}
void TextComponent::Render() const
{
	if (m_Texture != nullptr)
	{
		Renderer::GetInstance().RenderTexture(*m_Texture, m_WorldPosition.x, m_WorldPosition.y);
	}
}
void TextComponent::SetText(const std::string& text)
{
	m_Text = text;
}
void TextComponent::SetWorldPosition(float x, float y, float z)
{
	m_WorldPosition.x = x;
	m_WorldPosition.y = y;
	m_WorldPosition.z = z;
}
Float3 TextComponent::GetWorldPosition() const
{
	return m_WorldPosition;
}
const std::shared_ptr<Texture2D>& TextComponent::GetTexture() const
{
	return m_Texture;
}
void TextComponent::SetRelativePosition(float x, float y, float z)
{
	m_RelativePosition.x += x;
	m_RelativePosition.y += y;
	m_RelativePosition.z += z;
}
Float3 TextComponent::GetRelativePosition() const
{
	return m_RelativePosition;
}
void TextComponent::SetOwner(std::unique_ptr<dae::SceneObject> pOwner)
{
	m_pOwner = std::move(pOwner);
	m_WorldPosition += m_pOwner->GetTransform()->GetWorldPosition();
}