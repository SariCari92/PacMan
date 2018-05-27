#pragma once
#include "Scene.h"
#include "glm\vec4.hpp"

namespace dae
{
	class SceneObject;
}

class StartLevel : public dae::Scene
{
public:
	StartLevel();
	~StartLevel();

	virtual void Update(float deltaTime);
	virtual void Render() const;
private:
	void InitializeOptions();
	void InitializeButtonConfiguration();
private:	
	std::shared_ptr<dae::SceneObject> m_p1PlayerText;
	std::shared_ptr<dae::SceneObject> m_p2PlayerPacManText;
	std::shared_ptr<dae::SceneObject> m_p2PlayerTextPacManGhost;
	std::shared_ptr<dae::SceneObject> m_pSelectionIndicator;

	int m_SelectionIdx;
};
