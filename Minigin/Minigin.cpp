#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "Scene.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "SceneObject.h"
#include "Level1.h"
#include "StartLevel.h"

int dae::Minigin::m_WindowWidth = 600;
int dae::Minigin::m_WindowHeight = 630;

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	window = SDL_CreateWindow(
		"Programming 4 - End Assignment: PacMan",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		m_WindowWidth,
		m_WindowHeight,
		SDL_WINDOW_OPENGL
	);
	if (window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	std::shared_ptr<dae::Scene> startScene = std::shared_ptr<dae::Scene>(new StartLevel);
	dae::SceneManager::GetInstance().AddScene(startScene);
	dae::SceneManager::GetInstance().SetActiveScene(startScene);

	//std::shared_ptr<dae::Scene> playScene = std::shared_ptr<dae::Scene>(new Level1);
	//dae::SceneManager::GetInstance().AddScene(playScene);
	//dae::SceneManager::GetInstance().SetActiveScene(playScene);
	
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto previousTime = std::chrono::high_resolution_clock::now();
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		while (doContinue)
		{
			auto currentTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<float> elapsed = currentTime - previousTime;
			float deltaTime{ std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() / 1000.0f }; // deltaTime in Seconds

			doContinue = input.ProcessInput();
			sceneManager.Update(deltaTime);
			renderer.Render();

			previousTime = currentTime;
		}
	}

	Cleanup();
}
int dae::Minigin::GetSDL_WindowWidth()
{
	return m_WindowWidth;
}
int dae::Minigin::GetSDL_WindowHeight()
{
	return m_WindowHeight;
}

