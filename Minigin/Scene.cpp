#include "MiniginPCH.h"
#include "Scene.h"
#include "SceneObject.h"

unsigned int dae::Scene::idCounter = 0;

dae::Scene::Scene(const std::string& name) : m_Name(name) {}

dae::Scene::~Scene() = default;

void dae::Scene::Add(const std::shared_ptr<SceneObject>& object)
{
	m_Objects.push_back(object);
}

void dae::Scene::BaseUpdate(float deltaTime)
{
	for(auto gameObject : m_Objects)
	{
		gameObject->Update(deltaTime);
	}

	Update(deltaTime);
}

void dae::Scene::BaseRender() const
{
	for (const auto gameObject : m_Objects)
	{
		gameObject->Render();
	}
	Render();
}

void dae::Scene::Update(float deltaTime)
{

}
void dae::Scene::Render() const
{

}

