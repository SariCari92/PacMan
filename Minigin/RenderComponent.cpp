#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Renderer.h"

RenderComponent::RenderComponent()
{

}
RenderComponent::~RenderComponent()
{

}

void RenderComponent::Update()
{

}

void RenderComponent::Render(const TextComponent &textComponent, TextureComponent& textureComponent)
{
	auto textTexture = textComponent.GetTexture();
	if (textTexture != nullptr)
	{
		const auto pos = textComponent.GetPosition();
		Renderer::GetInstance().RenderTexture(*textTexture, pos.x, pos.y);
	}
	auto textureTexture = textureComponent.GetTexture();
	if (textureTexture != nullptr)
	{
		const auto pos = textureComponent.GetPosition();
		Renderer::GetInstance().RenderTexture(*textureTexture, pos.x, pos.y);
	}
	
}