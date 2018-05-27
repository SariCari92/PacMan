#pragma once
#include "SceneManager.h"

namespace dae
{
	class SceneObject;
	class Scene
	{	
	public:
		explicit Scene(const std::string& name);
		~Scene();

		void Add(const std::shared_ptr<SceneObject>& object);
		void Remove(std::shared_ptr<SceneObject>& object, bool isDelete);
		void BaseUpdate(float deltaTime);
		void BaseRender() const;


		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	protected: 
		virtual void Update(float deltaTime);
		virtual void Render() const;

		std::string m_Name{};
		std::vector < std::shared_ptr<SceneObject>> m_Objects{};

		static unsigned int idCounter; 
	};

}
