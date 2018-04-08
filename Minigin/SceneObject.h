#pragma once
#include "ComponentBase.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include <typeinfo>

namespace dae
{
	class SceneObject
	{
	public:
		SceneObject();
		virtual ~SceneObject() = default;

		virtual void Update();
		virtual void Render() const;
		void AddComponent(std::shared_ptr<ComponentBase> component);
		template<typename T> std::shared_ptr<T> GetComponent() const;
		std::shared_ptr<TransformComponent> GetTransform() const;

	protected:
		std::vector<std::shared_ptr<ComponentBase>> m_Components;
		std::shared_ptr<TransformComponent> m_pTransformComponent;

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
		const type_info& typeId = typeid(T) ;
		if (typeId == typeid(*component))
		{
			return std::static_pointer_cast<T>(component);
		}
	}
	
	return nullptr;
}