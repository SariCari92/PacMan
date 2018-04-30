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

	virtual void Update(float deltaTime) = 0;
	virtual void Render() const = 0;
	virtual void SetOwner(dae::SceneObject *pOwner);

protected:
	dae::SceneObject *m_pOwner;
};
