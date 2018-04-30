#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void Update(float deltaTime);
		void Render();
		void AddScene(std::shared_ptr<Scene> pScene);
		void SetActiveScene(std::shared_ptr<Scene> pActiveScene);

	private:
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		std::shared_ptr<Scene> m_pActiveScene;
	};

}
