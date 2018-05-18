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
	, m_GridSize{ 30 }, m_RowNr{ 20 }, m_ColNr{20}
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
}
void Level1::Update(float deltaTime)
{

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
		}
	}
}

void Level1::InitializePacMan()
{
	m_pPacMan = std::make_shared<dae::SceneObject>();
	//Texture
	std::shared_ptr<TextureComponent> pPacManTexture = std::make_shared<TextureComponent>("PacMan.png");
	m_pPacMan->AddComponent(pPacManTexture);
	Add(m_pPacMan);
	//Input
	m_pPacMan->AddComponent(std::shared_ptr<InputComponent>(new InputComponentPacMan(0)));
	//Set Grid Info
	int initRow{ 1 };
	int initCol{ 1 };
	m_pPacMan->GetTransform()->Translate((float)m_Grids[initRow][initCol]->rect.x, (float)m_Grids[initRow][initCol]->rect.y, 0.0f);
	//MovementComponent
	std::shared_ptr<MovementComponent> movComp = std::make_shared<MovementComponent>();
	movComp->SetCurrentGrid(m_Grids[initRow][initCol]);
	m_pPacMan->AddComponent(movComp);
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
			//Grid pGrid{};
			//pGrid.rect = CreateSDLRectangle(col * m_GridSize, row * m_GridSize, m_GridSize, m_GridSize);
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
	for (int col{ 8 }; col < 12; ++col)
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
}