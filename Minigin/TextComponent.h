#pragma once
#include "ComponentBase.h"
#include "Transform.h"
#include "Font.h"
#include "Texture2D.h"
#include "Structs.h"

using namespace dae;

class TextComponent final : public ComponentBase
{
public:
	TextComponent();
	TextComponent(const std::string& text, std::shared_ptr<Font> font);
	~TextComponent();

	void Update() override;
	void Render() const override;
	void SetText(const std::string& text);

	void SetWorldPosition(float x, float y, float z);
	Float3 GetWorldPosition() const;
	void SetRelativePosition(float x, float y, float z);
	Float3 GetRelativePosition() const;

	const std::shared_ptr<Texture2D>& GetTexture() const;
	void SetOwner(std::unique_ptr<dae::SceneObject> pOwner) override;

private:
	bool m_NeedsUpdate;
	std::string m_Text;
	Float3 m_WorldPosition;
	Float3 m_RelativePosition;
	std::shared_ptr<Font> m_Font;
	std::shared_ptr<Texture2D> m_Texture;
};
