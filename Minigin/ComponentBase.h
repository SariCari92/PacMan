#pragma once
namespace dae
{
	class SceneObject;
}

class ComponentBase
{
public:
	ComponentBase();
	virtual ~ComponentBase();

	virtual void Update() = 0;
	virtual void Render() const = 0;
	virtual void SetOwner(std::unique_ptr<dae::SceneObject> pOwner);

protected:
	std::unique_ptr<dae::SceneObject> m_pOwner;
};
