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
	void InitializeGhosts();
	void InitializeObstacles();

	void CheckCollisionPacManAndGhosts();
	void UpdatePacManScores();
	void CheckPlayToSuperMode();
	void CheckSuperModeToPlay();
	void RespawnGhost(std::shared_ptr<dae::SceneObject> ghost);
private:
	//Pacman(s)
	std::shared_ptr<dae::SceneObject> m_pScoreTextObject;
	std::vector<dae::SceneObject> m_PacManLives;
	std::vector<std::shared_ptr<dae::SceneObject>> m_PacMans;
	std::vector<std::shared_ptr<dae::SceneObject>> m_ScoreTextObjects;
	//Ghosts
	std::shared_ptr<dae::SceneObject> m_pBlinky;
	std::shared_ptr<dae::SceneObject> m_pClyde;
	std::shared_ptr<dae::SceneObject> m_pInky;
	std::shared_ptr<dae::SceneObject> m_pPinky;
	//Grid
	int m_RowNr;
	int m_ColNr;
	std::vector<std::vector<std::shared_ptr<Grid>>> m_Grids;
	int m_GridSize;
	//Level
	enum class LevelState
	{
		start,
		play,
		pacmanDead,
		superMode,
		gameOver
	};
	LevelState m_LevelState;
	float m_LevelStartTimer;
	float m_LevelStartTimerLeft;
	float m_PacManRespawnTimer;
	float m_PacManRespawnTimerLeft;
};