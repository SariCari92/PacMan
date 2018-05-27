#include "MiniginPCH.h"
#include "Level1.h"
#include "SceneObject.h"
#include "TextureComponent.h"
#include "InputComponent.h"
#include "InputComponentPacman.h"
#include "MovementComponent.h"
#include <SDL_render.h>
#include "Renderer.h"
#include "Helper.h"
#include "Minigin.h"
#include "TextComponent.h"
#include "HealthAndScoreComponent.h"
#include "Texture2D.h"
#include "GhostAIComponent.h"
#include "GameData.h"

Level1::Level1()
	:dae::Scene("Level1")
	, m_GridSize{ 30 }, m_RowNr{ 20 }, m_ColNr{ 20 }
	, m_pScoreTextObject{nullptr}
	, m_LevelState{}
	, m_LevelStartTimer{3.0f}, m_LevelStartTimerLeft{ m_LevelStartTimer }
	, m_PacManRespawnTimer{3.0f}, m_PacManRespawnTimerLeft{ m_PacManRespawnTimer }
{
	InitializeLevel();
}
Level1::~Level1()
{

}

void Level1::InitializeLevel()
{
	InitializeObstacles();
	InitializePacMan();
	InitializeGhosts();
}
void Level1::Update(float deltaTime)
{

	switch (m_LevelState)
	{
	case Level1::LevelState::start:
		m_LevelState = LevelState::play;
		break;
	case Level1::LevelState::play:
	{
		UpdatePacManScores();
		CheckPlayToSuperMode();
		CheckCollisionPacManAndGhosts();
		break;
	}
	case Level1::LevelState::pacmanDead:
		m_LevelState = LevelState::play;
		break;
	case Level1::LevelState::superMode:
		UpdatePacManScores();
		CheckSuperModeToPlay();
		CheckCollisionPacManAndGhosts();
		break;
	case Level1::LevelState::gameOver:
		break;
	}


}
void Level1::Render() const
{
	//Render Obstacles
	SDL_Renderer *renderer = Renderer::GetInstance().GetSDLRenderer();
	SDL_SetRenderDrawColor(renderer, 0, 0, 156, SDL_ALPHA_OPAQUE);

	for (int row{ 0 }; row < m_RowNr; ++row)
	{
		for (int col{ 0 }; col < m_ColNr; ++col)
		{
			if (m_Grids[row][col]->isObstacle)
			{
				DrawFilledRectangle(&m_Grids[row][col]->rect, CreateSDLColor(0, 0, 255, 255));
			}
			if(m_Grids[row][col]->point)DrawFilledRectangle(m_Grids[row][col]->point.get(), CreateSDLColor(255, 255, 0, 1));
			if (m_Grids[row][col]->specialPoint)DrawFilledRectangle(m_Grids[row][col]->specialPoint.get(), CreateSDLColor(0, 255, 0, 1));
		}
	}

	//Render Pacman Lives Icons
	int lives{ m_PacMans[0]->GetComponent<HealthAndScoreComponent>()->GetLives() };
	const std::shared_ptr<Texture2D> texture = m_PacMans[0]->GetComponent<TextureComponent>()->GetTexture();
	
	for (int i{ 0 }; i < lives; ++i)
	{
		dae::Renderer::GetInstance().RenderTexture(*texture, (float)m_GridSize * i, (float)dae::Minigin::GetSDL_WindowHeight() - 30);
	}

	if (m_PacMans.size() == 2)
	{
		lives = m_PacMans[1]->GetComponent<HealthAndScoreComponent>()->GetLives();
		const std::shared_ptr<Texture2D> texture2 = m_PacMans[1]->GetComponent<TextureComponent>()->GetTexture();

		for (int i{ 0 }; i < lives; ++i)
		{
			dae::Renderer::GetInstance().RenderTexture(*texture2, 120 + (float)m_GridSize * i, (float)dae::Minigin::GetSDL_WindowHeight() - 30);
		}
	}

}

void Level1::InitializePacMan()
{
	//First player is always initialized
	std::shared_ptr<dae::SceneObject> pPacMan = std::make_shared<dae::SceneObject>();
	std::shared_ptr<TextureComponent> pPacManTexture = std::make_shared<TextureComponent>("PacMan.png");
	pPacMan->AddComponent(pPacManTexture);
	//Input
	pPacMan->AddComponent(std::shared_ptr<InputComponent>(new InputComponentPacMan(0)));
	//Set Grid Info
	int initRow{ 1 };
	int initCol{ 1 };
	pPacMan->GetTransform()->Translate((float)m_Grids[initRow][initCol]->rect.x, (float)m_Grids[initRow][initCol]->rect.y, 0.0f);
	//MovementComponent
	std::shared_ptr<MovementComponent> movComp = std::make_shared<MovementComponent>();
	movComp->SetCurrentGrid(m_Grids[initRow][initCol]);
	pPacMan->AddComponent(movComp);
	//Score Component
	pPacMan->AddComponent(std::make_shared<HealthAndScoreComponent>());
	//Add To vector
	m_PacMans.push_back(pPacMan);
	Add(pPacMan);
	//Initialize Score Text
	m_ScoreTextObjects.push_back(std::make_shared<dae::SceneObject>());
	std::shared_ptr<TextComponent> scoreTextComponent = std::make_shared<TextComponent>("Score: ", std::make_shared<Font>("../Data/Lingua.otf", 32));
	m_ScoreTextObjects[0]->AddComponent(scoreTextComponent);
	m_ScoreTextObjects[0]->GetTransform()->Translate(dae::Minigin::GetSDL_WindowWidth() - 150.0f, dae::Minigin::GetSDL_WindowHeight() - 30.0f, 0.0f);
	Add(m_ScoreTextObjects[0]);

	switch (GameData::GetInstance().GetGameMode())
	{
	case GameData::GameMode::onePlayer:
	{

		break;
	}
	case GameData::GameMode::twoPlayerPacman:
	{
		std::shared_ptr<dae::SceneObject> pPacMan2 = std::make_shared<dae::SceneObject>();
		pPacManTexture = std::make_shared<TextureComponent>("PacMan.png");
		pPacMan2->AddComponent(pPacManTexture);
		//Input
		pPacMan2->AddComponent(std::shared_ptr<InputComponent>(new InputComponentPacMan(1)));
		//Set Grid Info
		initRow = 1 ;
		initCol = 3 ;
		pPacMan2->GetTransform()->Translate((float)m_Grids[initRow][initCol]->rect.x, (float)m_Grids[initRow][initCol]->rect.y, 0.0f);
		//MovementComponent
		movComp = std::make_shared<MovementComponent>();
		movComp->SetCurrentGrid(m_Grids[initRow][initCol]);
		pPacMan2->AddComponent(movComp);
		//Score Component
		pPacMan2->AddComponent(std::make_shared<HealthAndScoreComponent>());
		//Add To vector
		m_PacMans.push_back(pPacMan2);
		Add(pPacMan2);
		////Initialize Score Text
		m_ScoreTextObjects.push_back(std::make_shared<dae::SceneObject>());
		m_ScoreTextObjects[1]->AddComponent(std::make_shared<TextComponent>("Score: ", std::make_shared<Font>("../Data/Lingua.otf", 32)));
		m_ScoreTextObjects[1]->GetTransform()->Translate(dae::Minigin::GetSDL_WindowWidth() - 350.0f, dae::Minigin::GetSDL_WindowHeight() - 30.0f, 0.0f);
		Add(m_ScoreTextObjects[1]);
		break;
	}
	case GameData::GameMode::twoPlayerpacmanAndGhost:
	{
		break;
	}

	}
}

void Level1::InitializeGhosts()
{
	std::shared_ptr<MovementComponent> movComp = std::make_shared<MovementComponent>();

	switch (GameData::GetInstance().GetGameMode())
	{
	case GameData::GameMode::onePlayer:
		m_pBlinky = std::make_shared<dae::SceneObject>();
		m_pBlinky->AddComponent(std::make_shared<TextureComponent>("../Data/Blinky.png"));
		m_pBlinky->GetTransform()->Translate((float)m_Grids[7][7]->rect.x, (float)m_Grids[7][7]->rect.y, 0.0f);
		movComp->SetCurrentGrid(m_Grids[7][7]);
		m_pBlinky->AddComponent(movComp);
		m_pBlinky->AddComponent(std::make_shared<GhostAIComponent>());
		Add(m_pBlinky);
		break;
	case GameData::GameMode::twoPlayerPacman:
		m_pBlinky = std::make_shared<dae::SceneObject>();
		m_pBlinky->AddComponent(std::make_shared<TextureComponent>("../Data/Blinky.png"));
		m_pBlinky->GetTransform()->Translate((float)m_Grids[7][7]->rect.x, (float)m_Grids[7][7]->rect.y, 0.0f);
		movComp->SetCurrentGrid(m_Grids[7][7]);
		m_pBlinky->AddComponent(movComp);
		m_pBlinky->AddComponent(std::make_shared<GhostAIComponent>());
		Add(m_pBlinky);
		break;
	case GameData::GameMode::twoPlayerpacmanAndGhost:
		m_pBlinky = std::make_shared<dae::SceneObject>();
		m_pBlinky->AddComponent(std::make_shared<TextureComponent>("../Data/Blinky.png"));
		m_pBlinky->GetTransform()->Translate((float)m_Grids[7][7]->rect.x, (float)m_Grids[7][7]->rect.y, 0.0f);
		movComp->SetCurrentGrid(m_Grids[7][7]);
		m_pBlinky->AddComponent(movComp);
		std::shared_ptr<InputComponentPacMan> inputComp = std::make_shared<InputComponentPacMan>(1);
		m_pBlinky->AddComponent(inputComp);
		Add(m_pBlinky);
		break;
	}



	m_pClyde = std::make_shared<dae::SceneObject>();
	m_pClyde->AddComponent(std::make_shared<TextureComponent>("../Data/Clyde.png"));
	m_pClyde->GetTransform()->Translate((float)m_Grids[9][9]->rect.x, (float)m_Grids[9][10]->rect.y, 0.0f);
	movComp = std::make_shared<MovementComponent>();
	movComp->SetCurrentGrid(m_Grids[9][9]);
	m_pClyde->AddComponent(movComp);
	m_pClyde->AddComponent(std::make_shared<GhostAIComponent>());
	Add(m_pClyde);

	m_pInky = std::make_shared<dae::SceneObject>();
	m_pInky->AddComponent(std::make_shared<TextureComponent>("../Data/Inky.png"));
	m_pInky->GetTransform()->Translate((float)m_Grids[9][10]->rect.x, (float)m_Grids[9][11]->rect.y, 0.0f);
	movComp = std::make_shared<MovementComponent>();
	movComp->SetCurrentGrid(m_Grids[9][10]);
	m_pInky->AddComponent(movComp);
	m_pInky->AddComponent(std::make_shared<GhostAIComponent>());
	Add(m_pInky);

	m_pPinky = std::make_shared<dae::SceneObject>();
	m_pPinky->AddComponent(std::make_shared<TextureComponent>("../Data/Pinky.png"));
	m_pPinky->GetTransform()->Translate((float)m_Grids[7][12]->rect.x, (float)m_Grids[7][12]->rect.y, 0.0f);
	movComp = std::make_shared<MovementComponent>();
	movComp->SetCurrentGrid(m_Grids[7][12]);
	m_pPinky->AddComponent(movComp);
	m_pPinky->AddComponent(std::make_shared<GhostAIComponent>());
	Add(m_pPinky);
}

void Level1::InitializeObstacles()
{
	//Initialize Grids -> Rects
	for (int row{ 0 }; row < m_RowNr; ++row)
	{
		m_Grids.push_back(std::vector<std::shared_ptr<Grid>>());
		m_Grids[row].reserve(m_ColNr);
		for (int col{ 0 }; col < m_ColNr; ++col)
		{
			std::shared_ptr<Grid> pGrid = std::make_shared<Grid>();
			pGrid->rect = CreateSDLRectangle(col * m_GridSize, row * m_GridSize, m_GridSize, m_GridSize);
			m_Grids[row].push_back(pGrid);
		}
	}
	//Initialize Grids -> Adjacent Grids
	for (int row{ 0 }; row < m_RowNr; ++row)
		for (int col{ 0 }; col < m_ColNr; ++col)
		{
			std::shared_ptr<Grid> currGrid = m_Grids[row][col];
			currGrid->adjGrids.resize(9);
			currGrid->adjGrids[4] = m_Grids[row][col];

			if (row != 0)
			{
				currGrid->adjGrids[1] = m_Grids[row - 1][col];
				if (col != 0)
				{
					currGrid->adjGrids[0] = m_Grids[row - 1][col - 1];
				}
				if (col != m_ColNr - 1)
				{
					currGrid->adjGrids[2] = m_Grids[row - 1][col + 1];
				}
			}

			if (row != m_RowNr - 1)
			{
				currGrid->adjGrids[7] = m_Grids[row + 1][col];
				if (col != 0)
				{
					currGrid->adjGrids[6] = m_Grids[row + 1][col - 1];
				}
				if (col != m_ColNr - 1)
				{
					currGrid->adjGrids[8] = m_Grids[row + 1][col + 1];
				}
			}

			if (col != 0)
			{
				currGrid->adjGrids[3] = m_Grids[row][col - 1];
				if (row != 0)
				{
					currGrid->adjGrids[0] = m_Grids[row - 1][col - 1];
				}
				if (row != m_RowNr - 1)
				{
					currGrid->adjGrids[6] = m_Grids[row + 1][col - 1];
				}
			}
			if (col != m_ColNr - 1)
			{
				currGrid->adjGrids[5] = m_Grids[row][col + 1];
				if (row != 0)
				{
					currGrid->adjGrids[2] = m_Grids[row - 1][col + 1];
				}
				if (row != m_RowNr - 1)
				{
					currGrid->adjGrids[8] = m_Grids[row + 1][col + 1];
				}
			}
		}
	//Initialize Grids -> Is Obstacle
	for(int row{0}; row < m_RowNr; ++row)
		for(int col{0}; col <m_ColNr; ++col)
			m_Grids[row][col]->isObstacle = true;
	//Specify Flags(Generate Map by setting Flags)
	//Long Rows
	int pointSize{ 6 };
	(pointSize);
	for (int col{ 1 }; col < m_ColNr - 1; ++col)
	{
		m_Grids[1][col]->isObstacle = false;
		SDL_Rect point = CreateSDLRectangle(m_Grids[1][col]->rect.x + m_GridSize / 2 - pointSize / 2, m_Grids[1][col]->rect.y + m_GridSize / 2 - pointSize / 2, pointSize, pointSize);
		m_Grids[1][col]->point = std::make_unique<SDL_Rect>(point);
	}
	for (int col{ 1 }; col < m_ColNr - 1; ++col)
	{
		m_Grids[4][col]->isObstacle = false;
		SDL_Rect point = CreateSDLRectangle(m_Grids[4][col]->rect.x + m_GridSize / 2 - pointSize / 2, m_Grids[4][col]->rect.y + m_GridSize / 2 - pointSize / 2, pointSize, pointSize);
		m_Grids[4][col]->point = std::make_unique<SDL_Rect>(point);
	}
	for (int col{ 6 }; col < 14 ; ++col)
	{
		m_Grids[7][col]->isObstacle = false;
		SDL_Rect point = CreateSDLRectangle(m_Grids[7][col]->rect.x + m_GridSize / 2 - pointSize / 2, m_Grids[7][col]->rect.y + m_GridSize / 2 - pointSize / 2, pointSize, pointSize);
		m_Grids[7][col]->point = std::make_unique<SDL_Rect>(point);
	}	
	for (int col{ 9 }; col < 11; ++col)
	{
		m_Grids[9][col]->isObstacle = false;
		SDL_Rect point = CreateSDLRectangle(m_Grids[9][col]->rect.x + m_GridSize / 2 - pointSize / 2, m_Grids[9][col]->rect.y + m_GridSize / 2 - pointSize / 2, pointSize, pointSize);
		m_Grids[9][col]->point = std::make_unique<SDL_Rect>(point);
	}
	for (int col{ 1 }; col < m_ColNr - 1; ++col)
	{
		m_Grids[16][col]->isObstacle = false;
		SDL_Rect point = CreateSDLRectangle(m_Grids[16][col]->rect.x + m_GridSize / 2 - pointSize / 2, m_Grids[16][col]->rect.y + m_GridSize / 2 - pointSize / 2, pointSize, pointSize);
		m_Grids[16][col]->point = std::make_unique<SDL_Rect>(point);
	}
	for (int col{ 4 }; col < 16; ++col)
	{
		m_Grids[11][col]->isObstacle = false;
		SDL_Rect point = CreateSDLRectangle(m_Grids[11][col]->rect.x + m_GridSize / 2 - pointSize / 2, m_Grids[11][col]->rect.y + m_GridSize / 2 - pointSize / 2, pointSize, pointSize);
		m_Grids[11][col]->point = std::make_unique<SDL_Rect>(point);
	}
	for (int col{ 8 }; col < 12; ++col)
	{
		m_Grids[12][col]->isObstacle = false;
		SDL_Rect point = CreateSDLRectangle(m_Grids[12][col]->rect.x + m_GridSize / 2 - pointSize / 2, m_Grids[12][col]->rect.y + m_GridSize / 2 - pointSize / 2, pointSize, pointSize);
		m_Grids[12][col]->point = std::make_unique<SDL_Rect>(point);
	}
	for (int col{ 6 }; col < 14; ++col)
	{
		m_Grids[14][col]->isObstacle = false;
		SDL_Rect point = CreateSDLRectangle(m_Grids[14][col]->rect.x + m_GridSize / 2 - pointSize / 2, m_Grids[14][col]->rect.y + m_GridSize / 2 - pointSize / 2, pointSize, pointSize);
		m_Grids[14][col]->point = std::make_unique<SDL_Rect>(point);
	}
	for (int col{ 1 }; col < m_ColNr - 1; ++col)
	{
		m_Grids[18][col]->isObstacle = false;
		SDL_Rect point = CreateSDLRectangle(m_Grids[18][col]->rect.x + m_GridSize / 2 - pointSize / 2, m_Grids[18][col]->rect.y + m_GridSize / 2 - pointSize / 2, pointSize, pointSize);
		m_Grids[18][col]->point = std::make_unique<SDL_Rect>(point);
	}
	//Long Columns
	for (int row{ 1 }; row < m_RowNr - 1; ++row)
	{
		m_Grids[row][1]->isObstacle = false;
		SDL_Rect point = CreateSDLRectangle(m_Grids[row][1]->rect.x + m_GridSize / 2 - pointSize / 2, m_Grids[row][1]->rect.y + m_GridSize / 2 - pointSize / 2, pointSize, pointSize);
		m_Grids[row][1]->point = std::make_unique<SDL_Rect>(point);
	}
	for (int row{ 1 }; row < 17; ++row)
	{
		m_Grids[row][4]->isObstacle = false;
		SDL_Rect point = CreateSDLRectangle(m_Grids[row][4]->rect.x + m_GridSize / 2 - pointSize / 2, m_Grids[row][4]->rect.y + m_GridSize / 2 - pointSize / 2, pointSize, pointSize);
		m_Grids[row][4]->point = std::make_unique<SDL_Rect>(point);
	}
	for (int row{ 6 }; row < 17; ++row)
	{
		m_Grids[row][6]->isObstacle = false;
		SDL_Rect point = CreateSDLRectangle(m_Grids[row][6]->rect.x + m_GridSize / 2 - pointSize / 2, m_Grids[row][6]->rect.y + m_GridSize / 2 - pointSize / 2, pointSize, pointSize);
		m_Grids[row][6]->point = std::make_unique<SDL_Rect>(point);
	}
	for (int row{ 1 }; row < 10; ++row)
	{
		m_Grids[row][9]->isObstacle = false;
		SDL_Rect point = CreateSDLRectangle(m_Grids[row][9]->rect.x + m_GridSize / 2 - pointSize / 2, m_Grids[row][9]->rect.y + m_GridSize / 2 - pointSize / 2, pointSize, pointSize);
		m_Grids[row][9]->point = std::make_unique<SDL_Rect>(point);
	}
	for (int row{ 1 }; row < 10; ++row)
	{
		m_Grids[row][10]->isObstacle = false;
		SDL_Rect point = CreateSDLRectangle(m_Grids[row][10]->rect.x + m_GridSize / 2 - pointSize / 2, m_Grids[row][10]->rect.y + m_GridSize / 2 - pointSize / 2, pointSize, pointSize);
		m_Grids[row][10]->point = std::make_unique<SDL_Rect>(point);
	}
	for (int row{ 6 }; row < 17; ++row)
	{
		m_Grids[row][13]->isObstacle = false;
		SDL_Rect point = CreateSDLRectangle(m_Grids[row][13]->rect.x + m_GridSize / 2 - pointSize / 2, m_Grids[row][13]->rect.y + m_GridSize / 2 - pointSize / 2, pointSize, pointSize);
		m_Grids[row][13]->point = std::make_unique<SDL_Rect>(point);
	}
	for (int row{ 1 }; row < 17; ++row)
	{
		m_Grids[row][15]->isObstacle = false;
		SDL_Rect point = CreateSDLRectangle(m_Grids[row][15]->rect.x + m_GridSize / 2 - pointSize / 2, m_Grids[row][15]->rect.y + m_GridSize / 2 - pointSize / 2, pointSize, pointSize);
		m_Grids[row][15]->point = std::make_unique<SDL_Rect>(point);
	}
	for (int row{ 1 }; row < m_RowNr - 1; ++row)
	{
		m_Grids[row][18]->isObstacle = false;
		SDL_Rect point = CreateSDLRectangle(m_Grids[row][18]->rect.x + m_GridSize / 2 - pointSize / 2, m_Grids[row][18]->rect.y + m_GridSize / 2 - pointSize / 2, pointSize, pointSize);
		m_Grids[row][18]->point = std::make_unique<SDL_Rect>(point);
	}
	//Details
	for (int col{ 2 }; col < 4; ++col)
	{
		m_Grids[10][col]->isObstacle = false;
		SDL_Rect point = CreateSDLRectangle(m_Grids[10][col]->rect.x + m_GridSize / 2 - pointSize / 2, m_Grids[10][col]->rect.y + m_GridSize / 2 - pointSize / 2, pointSize, pointSize);
		m_Grids[10][col]->point = std::make_unique<SDL_Rect>(point);
	}
	for (int col{ 16 }; col < 18; ++col)
	{
		m_Grids[10][col]->isObstacle = false;
		SDL_Rect point = CreateSDLRectangle(m_Grids[10][col]->rect.x + m_GridSize / 2 - pointSize / 2, m_Grids[10][col]->rect.y + m_GridSize / 2 - pointSize / 2, pointSize, pointSize);
		m_Grids[10][col]->point = std::make_unique<SDL_Rect>(point);
	}
	for (int col{ 9 }; col < 11; ++col)
	{
		m_Grids[13][col]->isObstacle = false;
		SDL_Rect point = CreateSDLRectangle(m_Grids[13][col]->rect.x + m_GridSize / 2 - pointSize / 2, m_Grids[13][col]->rect.y + m_GridSize / 2 - pointSize / 2, pointSize, pointSize);
		m_Grids[13][col]->point = std::make_unique<SDL_Rect>(point);
	}
	int bigPointSize{ 15 };
	SDL_Rect point = CreateSDLRectangle(m_Grids[1][16]->rect.x + m_GridSize / 2 - pointSize / 2, m_Grids[1][16]->rect.y + m_GridSize / 2 - pointSize / 2, bigPointSize, bigPointSize);
	m_Grids[1][16]->point.reset();
	m_Grids[1][16]->specialPoint = std::make_unique<SDL_Rect>(point);
}

void Level1::CheckCollisionPacManAndGhosts()
{
	if (m_LevelState == LevelState::superMode)
	{
		for (std::shared_ptr<dae::SceneObject> pPacman : m_PacMans)
		{
			SDL_Rect pacmanCollBox = pPacman->GetComponent<MovementComponent>()->GetCollisionBox();
			if (SDL_HasIntersection(&m_pBlinky->GetComponent<MovementComponent>()->GetCollisionBox(), &pacmanCollBox))
			{
				pPacman->GetComponent<HealthAndScoreComponent>()->IncrementScore(10);
				RespawnGhost(m_pBlinky);
			}
			else if (SDL_HasIntersection(&m_pClyde->GetComponent<MovementComponent>()->GetCollisionBox(), &pacmanCollBox))
			{
				pPacman->GetComponent<HealthAndScoreComponent>()->IncrementScore(10);
				RespawnGhost(m_pClyde);
			}
			else if (SDL_HasIntersection(&m_pInky->GetComponent<MovementComponent>()->GetCollisionBox(), &pacmanCollBox))
			{
				pPacman->GetComponent<HealthAndScoreComponent>()->IncrementScore(10);
				RespawnGhost(m_pInky);
			}
			else if (SDL_HasIntersection(&m_pPinky->GetComponent<MovementComponent>()->GetCollisionBox(), &pacmanCollBox))
			{
				pPacman->GetComponent<HealthAndScoreComponent>()->IncrementScore(10);
				RespawnGhost(m_pPinky);
			}
		}
	}
	else
	{
		bool isCollision{ false };
		for (std::shared_ptr<dae::SceneObject> pPacman : m_PacMans)
		{
			SDL_Rect pacmanCollBox = pPacman->GetComponent<MovementComponent>()->GetCollisionBox();
			if (SDL_HasIntersection(&m_pBlinky->GetComponent<MovementComponent>()->GetCollisionBox(), &pacmanCollBox))
			{
				pPacman->GetComponent<HealthAndScoreComponent>()->DecrementLives();
				m_LevelState = LevelState::pacmanDead;
				isCollision = true;
			}
			else if (SDL_HasIntersection(&m_pClyde->GetComponent<MovementComponent>()->GetCollisionBox(), &pacmanCollBox))
			{
				pPacman->GetComponent<HealthAndScoreComponent>()->DecrementLives();
				m_LevelState = LevelState::pacmanDead;
				isCollision = true;
			}
			else if (SDL_HasIntersection(&m_pInky->GetComponent<MovementComponent>()->GetCollisionBox(), &pacmanCollBox))
			{
				pPacman->GetComponent<HealthAndScoreComponent>()->DecrementLives();
				m_LevelState = LevelState::pacmanDead;
				isCollision = true;
			}
			else if (SDL_HasIntersection(&m_pPinky->GetComponent<MovementComponent>()->GetCollisionBox(), &pacmanCollBox))
			{
				pPacman->GetComponent<HealthAndScoreComponent>()->DecrementLives();
				m_LevelState = LevelState::pacmanDead;
				isCollision = true;
			}

			if (pPacman->GetComponent<HealthAndScoreComponent>()->GetScore() == 0)
			{
				m_LevelState = LevelState::gameOver;
				return;
			}

			if (isCollision)
			{
				auto rect = m_Grids[10][1]->rect;
				pPacman->GetTransform()->SetWorldPosition(glm::vec3((float)rect.x, (float)rect.y, 0.0f));
				std::shared_ptr<MovementComponent> movComp = pPacman->GetComponent<MovementComponent>();
				movComp->SetCollisionBox(m_Grids[10][1]->rect);
				movComp->SetCurrentGrid(m_Grids[10][1]);
				movComp->SetMovementState(MovementComponent::MovementState::idle);
			}
		}
	}	
}

void Level1::UpdatePacManScores()
{

	std::string PacManScore1{ "Score: " };
	PacManScore1 += std::to_string(m_PacMans[0]->GetComponent<HealthAndScoreComponent>()->GetScore());
	m_ScoreTextObjects[0]->GetComponent<TextComponent>()->SetText(PacManScore1);
	m_ScoreTextObjects[0]->GetComponent<TextComponent>()->SetTextColor(glm::vec4{ 255.0f, 0.0f, 0.0f, 255.0f });


	if (m_PacMans.size() == 2)
	{
		std::string PacManScore2{ "Score: " };
		PacManScore2 += std::to_string(m_PacMans[1]->GetComponent<HealthAndScoreComponent>()->GetScore());
		m_ScoreTextObjects[1]->GetComponent<TextComponent>()->SetText(PacManScore2);
		m_ScoreTextObjects[1]->GetComponent<TextComponent>()->SetTextColor(glm::vec4{ 255.0f, 0.0f, 0.0f, 255.0f });
		
	}
}

void Level1::CheckPlayToSuperMode()
{
	for (std::shared_ptr<dae::SceneObject> pPacman : m_PacMans)
	{
		if (pPacman->GetComponent<HealthAndScoreComponent>()->GetIsSuperMode())
		{
			m_LevelState = LevelState::superMode;
			m_pBlinky->GetComponent<TextureComponent>()->SetTexture("../Data/ScaredGhost.png");
			m_pClyde->GetComponent<TextureComponent>()->SetTexture("../Data/ScaredGhost.png");
			m_pInky->GetComponent<TextureComponent>()->SetTexture("../Data/ScaredGhost.png");
			m_pPinky->GetComponent<TextureComponent>()->SetTexture("../Data/ScaredGhost.png");
			return;
		}
	}
}

void Level1::CheckSuperModeToPlay()
{
	for (std::shared_ptr<dae::SceneObject> pPacman : m_PacMans)//This is to avoid setting textures every frame. One time is sufficient
	{
		if (pPacman->GetComponent<HealthAndScoreComponent>()->GetIsSuperMode())
		{
			return;
		}
	}
	m_LevelState = LevelState::play;
	m_pBlinky->GetComponent<TextureComponent>()->SetTexture("../Data/Blinky.png");
	m_pClyde->GetComponent<TextureComponent>()->SetTexture("../Data/Clyde.png");
	m_pInky->GetComponent<TextureComponent>()->SetTexture("../Data/Inky.png");
	m_pPinky->GetComponent<TextureComponent>()->SetTexture("../Data/Pinky.png");
}

void Level1::RespawnGhost(std::shared_ptr<dae::SceneObject> ghost)
{
	std::shared_ptr<Grid> respawnGrid = m_Grids[9][10];
	SDL_Rect respawnRect = respawnGrid->rect;
	ghost->GetTransform()->SetWorldPosition(glm::vec3{ respawnRect.x, respawnRect.y, 0.0f });
	std::shared_ptr<MovementComponent> movComp = ghost->GetComponent<MovementComponent>();
	movComp->SetCollisionBox(respawnRect);
	movComp->SetCurrentGrid(respawnGrid);
	movComp->SetMovementState(MovementComponent::MovementState::idle);
}