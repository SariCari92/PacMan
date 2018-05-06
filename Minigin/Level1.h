#pragma once
#include "Scene.h"
#include <SDL_rect.h>

namespace dae
{
	class SceneObject;
}

class Level1 final : public dae::Scene
{
public:
	Level1();
	~Level1();
	void Update(float deltaTime) override;
	void Render() const override;
private:
	void InitializePacMan();
	void InitializeObstacles();
private:
	std::shared_ptr<dae::SceneObject> m_pPacMan;
	std::vector<std::shared_ptr<dae::SceneObject>> m_Walls;
	int m_WallThickness;
	int m_PathWidth;

	//Grid System
	int m_RowNr;
	int m_ColNr;
	std::vector<std::vector<bool>> m_ObstaclesFlag;
	std::vector<std::vector<SDL_Rect>> m_Obstacles;
	int m_GridSize;
};