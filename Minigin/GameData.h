#pragma once
#include "Singleton.h"

class GameData : public dae::Singleton<GameData>
{
public:
	enum class GameMode
	{
		onePlayer,
		twoPlayerPacman,
		twoPlayerpacmanAndGhost
	};

	void SetGameMode(GameMode mode);
	GameMode GetGameMode() const;
	int GetScore() const;

	GameData();
	~GameData();
private:
	GameMode m_GameMode;
	int m_Score;
};
