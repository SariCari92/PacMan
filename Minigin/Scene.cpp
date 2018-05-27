#include "MiniginPCH.h"
#include "Scene.h"
#include "SceneObject.h"
#include <algorithm>

unsigned int dae::Scene::idCounter = 0;

dae::Scene::Scene(const std::string& name) : m_Name(name) {}

dae::Scene::~Scene() = default;

void dae::Scene::Add(const std::shared_ptr<SceneObject>& object)
{
	m_Objects.push_back(object);
	object->SetScene(this);
}

void dae::Scene::Remove(std::shared_ptr<SceneObject>& object, bool isDelete)
{
	auto toDeleteIt = std::find(m_Objects.begin(), m_Objects.end(), object);
	m_Objects.erase(toDeleteIt);
	if(isDelete)
		object.reset();
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

