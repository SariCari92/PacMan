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
	TextureComponent(std::string texture);
	~TextureComponent();

	void Update() override;
	void Render() const override;
	void SetWorldPosition(Float3 newPos);
	Float3 GetWorldPosition() const;
	void SetRelativePosition(Float3 newPos);
	Float3 GetRelativePosition() const;
	void SetTexture(std::string texture);
	const std::shared_ptr<Texture2D> GetTexture() const;
	void SetOwner(std::unique_ptr<dae::SceneObject> pOwner) override;
private:
	std::shared_ptr<Texture2D> m_pTexture;
	Float3 m_WorldPosition;
	Float3 m_RelativePosition;
};
