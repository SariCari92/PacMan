#pragma once
#include "ComponentBase.h"
#include "TransformComponent.h"
#include "RenderComponent.h"

namespace dae
{
	class SceneObject
	{
	public:
		SceneObject() = default;
		virtual ~SceneObject() = default;

		virtual void Update() = 0;
		virtual void Render() const = 0;
		void AddComponent(std::shared_ptr<ComponentBase> component);
		template<typename T> std::shared_ptr<T> GetComponent() const;

	protected:
		std::vector<std::shared_ptr<ComponentBase>> m_Components;
		TransformComponent m_TransformComponent;

	public:
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
		type_info typeId = typeid(T);
		if (typeId == typeid(*component))
		{
			return std::static_pointer_cast<T>(component);
		}
	}
	
	return nullptr;
}