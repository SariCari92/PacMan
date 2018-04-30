#pragma once
#include "Scene.h"

namespace dae
{
	class SceneObject;
}

class Level1 final : public dae::Scene
{
public:
	Level1();
	~Level1();
private:
	void InitializePacMan();
private:
	std::shared_ptr<dae::SceneObject> m_pPacMan;
};