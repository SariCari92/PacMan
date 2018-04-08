#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"

TextureComponent::TextureComponent()
	:m_pTexture{ nullptr },
	m_Position{}
{

}
TextureComponent::TextureComponent(std::string texture)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(texture);
}
TextureComponent::~TextureComponent()
{

}

void TextureComponent::Update()
{

}
void TextureComponent::Render() const
{
	if (m_pTexture)
	{
		Renderer::GetInstance().RenderTexture(*m_pTexture, m_Position.x, m_Position.y);
	}
}
void TextureComponent::SetPosition(Float3 newPos)
{
	m_Position = newPos;
}
Float3 TextureComponent::GetPosition() const
{
	return m_Position;
}
void TextureComponent::SetTexture(std::string texture)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(texture);
}

const std::shared_ptr<Texture2D> TextureComponent::GetTexture() const
{
	return m_pTexture;
}