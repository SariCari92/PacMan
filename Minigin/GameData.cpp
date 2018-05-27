#include "MiniginPCH.h"
#include "GameData.h"

GameData::GameData()
	:m_Score{0}
{

}
GameData::~GameData()
{

}

void GameData::SetGameMode(GameMode mode)
{
	m_GameMode = mode;
}

GameData::GameMode GameData::GetGameMode() const
{
	return m_GameMode;
}
int GameData::GetScore() const
{
	return m_Score;
}