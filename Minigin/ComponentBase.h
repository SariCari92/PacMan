#pragma once
class SceneObject;

class ComponentBase
{
public:
	ComponentBase() = default;
	virtual ~ComponentBase() = default;

	virtual void Update() = 0;
	virtual void Render() const = 0;
};
