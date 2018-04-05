#pragma once

class ComponentBase
{
public:
	ComponentBase() = default;
	virtual ~ComponentBase() = default;

	virtual void Update() = 0;
};
