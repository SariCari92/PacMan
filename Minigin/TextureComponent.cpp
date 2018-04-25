#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "SceneObject.h"

TextureComponent::TextureComponent()
	:m_pTexture{ nullptr },
	m_WorldPosition{}
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
	if (m_pOwner) m_WorldPosition = m_pOwner->GetTransform()->GetWorldPosition() + m_RelativePosition;
}
void TextureComponent::Render() const
{
	if (m_pTexture)
	{
		Renderer::GetInstance().RenderTexture(*m_pTexture, m_WorldPosition.x, m_WorldPosition.y);
	}
}
void TextureComponent::SetWorldPosition(Float3 newPos)
{
	m_WorldPosition = newPos;
}
Float3 TextureComponent::GetWorldPosition() const
{
	return m_WorldPosition;
}
void TextureComponent::SetRelativePosition(Float3 newPos)
{
	m_RelativePosition = newPos;
}
Float3 TextureComponent::GetRelativePosition() const
{
	return m_RelativePosition;
}
void TextureComponent::SetTexture(std::string texture)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(texture);
}

const std::shared_ptr<Texture2D> TextureComponent::GetTexture() const
{
	return m_pTexture;
}
void TextureComponent::SetOwner(std::unique_ptr<dae::SceneObject> pOwner)
{
	m_pOwner = std::move(pOwner);
	m_WorldPosition += m_pOwner->GetTransform()->GetWorldPosition();
}