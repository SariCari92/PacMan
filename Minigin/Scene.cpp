#include "MiniginPCH.h"
#include "Scene.h"
#include "SceneObject.h"

unsigned int dae::Scene::idCounter = 0;

dae::Scene::Scene(const std::string& name) : mName(name) {}

dae::Scene::~Scene() = default;

void dae::Scene::Add(const std::shared_ptr<SceneObject>& object)
{
	mObjects.push_back(object);
}

void dae::Scene::BaseUpdate(float deltaTime)
{
	for(auto gameObject : mObjects)
	{
		gameObject->Update(deltaTime);
	}

	Update(deltaTime);
}

void dae::Scene::BaseRender() const
{
	for (const auto gameObject : mObjects)
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

