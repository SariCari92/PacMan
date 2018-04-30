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
		void Update(float deltaTime);
		void Render() const;

		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	protected: 
		

		std::string mName{};
		std::vector < std::shared_ptr<SceneObject>> mObjects{};

		static unsigned int idCounter; 
	};

}
