#include "MiniginPCH.h"
#include "Level1.h"
#include "SceneObject.h"
#include "TextureComponent.h"
#include "InputComponent.h"

Level1::Level1()
	:dae::Scene("Level1")
{
	InitializePacMan();
}
Level1::~Level1()
{

}

void Level1::InitializePacMan()
{
	m_pPacMan = std::make_shared<dae::SceneObject>();
	//Texture
	m_pPacMan->AddComponent(std::make_shared<TextureComponent>("PacMan.png"));
	Add(m_pPacMan);
	m_pPacMan->GetTransform()->Translate(50.0f, 10.0f, 0.0f);
	//Input
	m_pPacMan->AddComponent(std::make_shared<InputComponent>(0));
}