#pragma once
#include "Scene.h"
#include <SDL_rect.h>

namespace dae
{
	class SceneObject;
}

struct Grid;

class Level1 final : public dae::Scene
{
public:
	Level1();
	~Level1();
	void Update(float deltaTime) override;
	void Render() const override;
private:
	void InitializeLevel();
	void InitializePacMan();
	void InitializeObstacles();
private:
	std::shared_ptr<dae::SceneObject> m_pPacMan;

	int m_RowNr;
	int m_ColNr;
	std::vector<std::vector<std::shared_ptr<Grid>>> m_Grids;
	int m_GridSize;

	std::shared_ptr<dae::SceneObject> m_pScoreTextObject;
};