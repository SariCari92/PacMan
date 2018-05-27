#include "MiniginPCH.h"
#include "StartLevel.h"
#include "SceneObject.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "InputManager.h"
#include "Commands.h"
#include "GameData.h"
#include "SceneManager.h"
#include "Level1.h"
#include "InputComponentPacMan.h"

StartLevel::StartLevel()
	:Scene("StartLevel"), m_SelectionIdx{0}
{
	InitializeOptions();
	InitializeButtonConfiguration();
}
StartLevel::~StartLevel()
{

}

void StartLevel::Update(float deltaTime)
{
	float XOffset{ 100 };
	float YOffset{ 200 };

	auto &inputMan = InputManager::GetInstance();

	std::shared_ptr<Command> command =  inputMan.GetCommand(1, InputManager::PressState::Down);

	if (command)
	{
		const type_info& typeId = typeid(*command);
		if (typeId == typeid(MoveUpCommand))
		{
			--m_SelectionIdx;
			if (m_SelectionIdx < 0) m_SelectionIdx = 2;
		}
		else if (typeId == typeid(MoveDownCommand))
		{
			m_SelectionIdx = ++m_SelectionIdx % 3;
		}
		else if(typeId == typeid(SelectCommand))
		{

			switch (m_SelectionIdx)
			{
			case 0:
			{
				GameData::GetInstance().SetGameMode(GameData::GameMode::onePlayer);
				std::shared_ptr<dae::Scene> playScene{ new Level1() };
				dae::SceneManager::GetInstance().AddScene(playScene);
				dae::SceneManager::GetInstance().SetActiveScene(playScene);
				break;
			}
			case 1:
			{
				GameData::GetInstance().SetGameMode(GameData::GameMode::twoPlayerPacman);
				std::shared_ptr<dae::Scene> playScene{ new Level1() };
				dae::SceneManager::GetInstance().AddScene(playScene);
				dae::SceneManager::GetInstance().SetActiveScene(playScene);
				break;
			}
			case 2:
			{
				GameData::GetInstance().SetGameMode(GameData::GameMode::twoPlayerpacmanAndGhost);
				std::shared_ptr<dae::Scene> playScene{ new Level1() };
				dae::SceneManager::GetInstance().AddScene(playScene);
				dae::SceneManager::GetInstance().SetActiveScene(playScene);
				break;
			}
			}
		}
	}

	command = inputMan.GetCommand(0, InputManager::PressState::Down);

	if (command)
	{
		const type_info& typeId = typeid(*command);
		if (typeId == typeid(MoveUpCommand))
		{
			--m_SelectionIdx;
			if (m_SelectionIdx < 0) m_SelectionIdx = 2;
		}
		else if (typeId == typeid(MoveDownCommand))
		{
			m_SelectionIdx = ++m_SelectionIdx % 3;
		}
		else if (typeId == typeid(SelectCommand))
		{

			switch (m_SelectionIdx)
			{
			case 0:
			{
				GameData::GetInstance().SetGameMode(GameData::GameMode::onePlayer);
				std::shared_ptr<dae::Scene> playScene{ new Level1() };
				dae::SceneManager::GetInstance().AddScene(playScene);
				dae::SceneManager::GetInstance().SetActiveScene(playScene);
				break;
			}
			case 1:
			{
				GameData::GetInstance().SetGameMode(GameData::GameMode::twoPlayerPacman);
				std::shared_ptr<dae::Scene> playScene{ new Level1() };
				dae::SceneManager::GetInstance().AddScene(playScene);
				dae::SceneManager::GetInstance().SetActiveScene(playScene);
				break;
			}
			case 2:
			{
				GameData::GetInstance().SetGameMode(GameData::GameMode::twoPlayerpacmanAndGhost);
				std::shared_ptr<dae::Scene> playScene{ new Level1() };
				dae::SceneManager::GetInstance().AddScene(playScene);
				dae::SceneManager::GetInstance().SetActiveScene(playScene);
				break;
			}
			}
		}
	}

	m_pSelectionIndicator->GetTransform()->SetWorldPosition(glm::vec3(XOffset, YOffset + m_SelectionIdx * 100.0f, 0.0f));

}
void StartLevel::Render() const
{

}

void StartLevel::InitializeOptions()
{
	//Selection
	m_p1PlayerText = std::make_shared<dae::SceneObject>();
	std::shared_ptr<TextComponent> textComp = std::make_shared<TextComponent>("1 Player", std::make_shared<Font>("../Data/Lingua.otf", 24));
	textComp->SetTextColor(glm::vec4{255.0f, 0.0f, 0.0f, 255.0f});
	m_p1PlayerText->AddComponent(textComp);
	m_p1PlayerText->GetTransform()->Translate(150.0f, 200.0f, 0.0f);
	Add(m_p1PlayerText);

	m_p2PlayerPacManText = std::make_shared<dae::SceneObject>();
	textComp = std::make_shared<TextComponent>("2 Player: 2x Pacman", std::make_shared<Font>("../Data/Lingua.otf", 24));
	textComp->SetTextColor(glm::vec4{ 255.0f, 0.0f, 0.0f, 255.0f });
	m_p2PlayerPacManText->AddComponent(textComp);
	m_p2PlayerPacManText->GetTransform()->Translate(150.0f, 300.0f, 0.0f);
	Add(m_p2PlayerPacManText);

	m_p2PlayerTextPacManGhost = std::make_shared<dae::SceneObject>();
	textComp = std::make_shared<TextComponent>("2 Player: Pacman And Ghost", std::make_shared<Font>("../Data/Lingua.otf", 24));
	textComp->SetTextColor(glm::vec4{ 255.0f, 0.0f, 0.0f, 255.0f });
	m_p2PlayerTextPacManGhost->AddComponent(textComp);
	m_p2PlayerTextPacManGhost->GetTransform()->Translate(150.0f, 400.0f, 0.0f);
	Add(m_p2PlayerTextPacManGhost);

	m_pSelectionIndicator = std::make_shared<dae::SceneObject>();
	std::shared_ptr<TextureComponent> textureComp = std::make_shared<TextureComponent>("../Data/PacMan.png");
	m_pSelectionIndicator->AddComponent(textureComp);
	Add(m_pSelectionIndicator);
	m_pSelectionIndicator->GetTransform()->Translate(100.0f, 200.0f, 0.0f);
}

void StartLevel::InitializeButtonConfiguration()
{
	auto &inputMan = InputManager::GetInstance();
	//Initialize Buttons For Controller 1
	inputMan.SetGamepadUpCommand(0, std::make_shared<MoveUpCommand>());
	inputMan.SetGamepadDownCommand(0, std::make_shared<MoveDownCommand>());
	inputMan.SetGamepadACommand(0, std::make_shared<SelectCommand>());
	//Initialize Buttons For Controller 2
	inputMan.SetGamepadUpCommand(1, std::make_shared<MoveUpCommand>());
	inputMan.SetGamepadDownCommand(1, std::make_shared<MoveDownCommand>());
	inputMan.SetGamepadACommand(1, std::make_shared<SelectCommand>());
}