#pragma once
#include "ComponentBase.h"
#include <vector>
#include <SDL_rect.h>

struct Grid
{
	bool isObstacle;
	SDL_Rect rect;
	std::vector<std::weak_ptr<Grid>> adjGrids;
	std::unique_ptr<SDL_Rect> point;
};

class MovementComponent : public ComponentBase
{
public:
	MovementComponent();
	~MovementComponent();

	virtual void Update(float deltaTime) override;
	virtual void Render() const override;

	void MoveUp(float deltaTime);
	void MoveDown(float deltaTime);
	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);
	void SetCurrentGrid(std::shared_ptr<Grid> pGrid);
	std::shared_ptr<Grid> GetCurrentGrid() const;
	const SDL_Rect& GetCollisionBox() const;

	enum class MovementState
	{
		idle ,up, down, left, right
	};



private:
	float m_Speed;
	MovementState m_MovementState;
	std::shared_ptr<Grid> m_pCurrentGrid;
	SDL_Rect m_CollisionBox;
};
