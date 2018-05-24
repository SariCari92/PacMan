#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"


void dae::SceneManager::Update(float deltaTime)
{
	//for(auto scene : m_Scenes)
	//{
	//	scene->BaseUpdate(deltaTime);
	//}

	if (m_pActiveScene) m_pActiveScene->BaseUpdate(deltaTime);
}

void dae::SceneManager::Render()
{
	if (m_pActiveScene) m_pActiveScene->BaseRender();
}

void dae::SceneManager::AddScene(std::shared_ptr<Scene> pScene)
{
	m_Scenes.push_back(pScene);
}



void dae::SceneManager::SetActiveScene(std::shared_ptr<Scene> pActiveScene)
{
	m_pActiveScene = pActiveScene;
}

std::shared_ptr<dae::Scene> dae::SceneManager::GetActiveScene() const
{
	return m_pActiveScene;
}
