#pragma once
#include "ComponentBase.h"
#include "Texture2D.h"
#include <memory>
#include "Structs.h"

using namespace dae;

class TextureComponent : public ComponentBase
{
public:
	TextureComponent();
	TextureComponent(std::shared_ptr<Texture2D> texture);
	~TextureComponent();

	void Update() override;
	void Render() const override;
	void SetPosition(Float3 newPos);
	Float3 GetPosition() const;
	void SetTexture(std::shared_ptr<Texture2D> texture);
	const std::shared_ptr<Texture2D> GetTexture() const;
private:
	std::shared_ptr<Texture2D> m_Texture;
	Float3 m_Position;
};
