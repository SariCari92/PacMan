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
#include "PhysicsComponent.h"

Level1::Level1()
	:dae::Scene("Level1")
	, m_WallThickness{ 10 }, m_PathWidth{ 35 }, m_GridSize{ 30 }, m_RowNr{ 20 }, m_ColNr{20}
{
	InitializePacMan();
	InitializeObstacles();
}
Level1::~Level1()
{

}

void Level1::Update(float deltaTime)
{

}
void Level1::Render() const
{
	SDL_Renderer *renderer = Renderer::GetInstance().GetSDLRenderer();
	SDL_SetRenderDrawColor(renderer, 0, 0, 156, SDL_ALPHA_OPAQUE);

	for (int row{ 0 }; row < m_RowNr; ++row)
	{
		for (int col{ 0 }; col < m_ColNr; ++col)
		{
			if (m_ObstaclesFlag[row][col])
			{
				//SDL_RenderDrawRect(renderer, &m_Obstacles[row][col]);
				SDL_RenderFillRect(renderer, &m_Obstacles[row][col]);
			}
		}
	}
}

void Level1::InitializePacMan()
{
	m_pPacMan = std::make_shared<dae::SceneObject>();
	//Texture
	std::shared_ptr<TextureComponent> pPacManTexture = std::make_shared<TextureComponent>("PacMan.png");
	pPacManTexture->SetPivot(glm::vec3{12.0f, 12.0f, 0.0f});
	m_pPacMan->AddComponent(pPacManTexture);
	Add(m_pPacMan);
	m_pPacMan->GetTransform()->Translate((float)m_GridSize, (float)m_GridSize, 0.0f);
	//Input
	m_pPacMan->AddComponent(std::shared_ptr<InputComponent>(new InputComponentPacMan(0)));
	//MovementComponent
	m_pPacMan->AddComponent(std::make_shared<MovementComponent>());
	//PhysicsComponent
	m_pPacMan->AddComponent(std::make_shared<PhysicsComponent>());
	m_pPacMan->GetComponent<PhysicsComponent>()->SetCollisionBox(CreateSDLRectangle(0, 0, 25, 25));
}


void Level1::InitializeObstacles()
{
	int initPosX{ m_GridSize / 2 };
	int initPosy{ m_GridSize / 2 };

	//Initialize Rects
	for (int row{ 0 }; row < m_RowNr; ++row)
	{
		m_Obstacles.push_back(std::vector<SDL_Rect>());
		m_Obstacles[row].reserve(m_ColNr);
		for (int col{ 0 }; col < m_ColNr; ++col)
		{
			SDL_Rect rect = CreateSDLRectangle(initPosX + col * m_GridSize - m_GridSize / 2, initPosy + row * m_GridSize - m_GridSize / 2, m_GridSize, m_GridSize);
			m_Obstacles[row].push_back(rect);
		}
	}
	//Initialize Flag
	for (int row{ 0 }; row < m_RowNr; ++row)
	{
		m_ObstaclesFlag.push_back(std::vector<bool>());
		m_ObstaclesFlag[row].reserve(m_ColNr);
		for (int col{ 0 }; col < m_ColNr; ++col)
		{
			m_ObstaclesFlag[row].push_back(true);
		}
	}
	//Specify Flags(Generate Map by setting Flags)
	//Long Rows
	for (int col{ 1 }; col < m_ColNr - 1; ++col)
		m_ObstaclesFlag[1][col] = false;
	for (int col{ 1 }; col < m_ColNr - 1; ++col)
		m_ObstaclesFlag[4][col] = false;
	for (int col{ 6 }; col < 14 ; ++col)
		m_ObstaclesFlag[7][col] = false;
	for (int col{ 8 }; col < 12; ++col)
		m_ObstaclesFlag[9][col] = false;
	for (int col{ 1 }; col < m_ColNr - 1; ++col)
		m_ObstaclesFlag[16][col] = false;
	for (int col{ 4 }; col < 16; ++col)
		m_ObstaclesFlag[11][col] = false;
	for (int col{ 8 }; col < 12; ++col)
		m_ObstaclesFlag[12][col] = false;
	for (int col{ 6 }; col < 14; ++col)
		m_ObstaclesFlag[14][col] = false;
	for (int col{ 1 }; col < m_ColNr - 1; ++col)
		m_ObstaclesFlag[18][col] = false;
	//Long Columns
	for (int row{ 1 }; row < m_RowNr - 1; ++row)
		m_ObstaclesFlag[row][1] = false;
	for (int row{ 1 }; row < 17; ++row)
		m_ObstaclesFlag[row][4] = false;
	for (int row{ 6 }; row < 17; ++row)
		m_ObstaclesFlag[row][6] = false;
	for (int row{ 1 }; row < 10; ++row)
		m_ObstaclesFlag[row][9] = false;
	for (int row{ 1 }; row < 10; ++row)
		m_ObstaclesFlag[row][10] = false;
	for (int row{ 6 }; row < 17; ++row)
		m_ObstaclesFlag[row][13] = false;
	for (int row{ 1 }; row < 17; ++row)
		m_ObstaclesFlag[row][15] = false;
	for (int row{ 1 }; row < m_RowNr - 1; ++row)
		m_ObstaclesFlag[row][18] = false;
	//Details
	for (int col{ 2 }; col < 4; ++col)
		m_ObstaclesFlag[10][col] = false;
	for (int col{ 16 }; col < 18; ++col)
		m_ObstaclesFlag[10][col] = false;
	for (int col{ 9 }; col < 11; ++col)
		m_ObstaclesFlag[13][col] = false;
}