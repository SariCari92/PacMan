#pragma once
#include "ComponentBase.h"
#include "TransformComponent.h"
#include <typeinfo>
#include "Scene.h"

namespace dae
{
	class SceneObject
	{
	public:
		SceneObject();
		virtual ~SceneObject();

		virtual void Update(float deltaTime);
		virtual void Render() const;

		void AddComponent(std::shared_ptr<ComponentBase> pComponent);
		template<typename T> std::shared_ptr<T> GetComponent() const;
		std::shared_ptr<TransformComponent> GetTransform() const;
		void AddChild(std::shared_ptr<SceneObject> pChild);
		std::vector<std::shared_ptr<SceneObject>>& GetChildren() ;
		SceneObject* GetParent() const;
		void SetScene(dae::Scene *scene);
		dae::Scene* GetScene() const;

	protected:
		std::vector<std::shared_ptr<SceneObject>> m_Children;
		std::vector<std::shared_ptr<ComponentBase>> m_Components;
		std::shared_ptr<TransformComponent> m_pTransformComponent;
		SceneObject *m_pParent;
		dae::Scene *m_pScene;

	private:
		SceneObject(const SceneObject& other) = delete;
		SceneObject(SceneObject&& other) = delete;
		SceneObject& operator=(const SceneObject& other) = delete;
		SceneObject& operator=(SceneObject&& other) = delete;
	};
}

template<typename T>
std::shared_ptr<T> dae::SceneObject::GetComponent() const
{
	for (std::shared_ptr<ComponentBase> component : m_Components)
	{
		const type_info& typeId = typeid(T);
		if (typeId == typeid(*component))
		{
			return std::static_pointer_cast<T>(component);
		}
	}
	
	return nullptr;
}