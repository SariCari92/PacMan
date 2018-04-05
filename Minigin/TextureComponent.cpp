#include "MiniginPCH.h"
#include "TextureComponent.h"

TextureComponent::TextureComponent()
{

}
TextureComponent::TextureComponent(std::shared_ptr<Texture2D> texture)
	:m_Texture{texture}
{

}
TextureComponent::~TextureComponent()
{

}

void TextureComponent::Update()
{

}
void TextureComponent::SetPosition(Float3 newPos)
{
	m_Position = newPos;
}
Float3 TextureComponent::GetPosition() const
{
	return m_Position;
}
void TextureComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_Texture = texture;
}

const std::shared_ptr<Texture2D> TextureComponent::GetTexture() const
{
	return m_Texture;
}