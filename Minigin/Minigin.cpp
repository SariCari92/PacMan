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


void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
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
	std::shared_ptr<dae::Scene> scene = std::shared_ptr<dae::Scene>(new Level1);
	dae::SceneManager::GetInstance().AddScene(scene);
	dae::SceneManager::GetInstance().SetActiveScene(scene);


	//auto go = std::make_shared<GameObject>();
	//go->SetTexture("background.jpg");
	//scene.Add(go);

	//go = std::make_shared<GameObject>();
	//go->SetTexture("logo.png");
	//go->SetPosition(216, 180);
	//scene.Add(go);

	//auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//auto to = std::make_shared<TextObject>("Programming 4 Assignment", font);
	//to->SetPosition(80, 20);
	//scene.Add(to);

	//========================================================================

	std::shared_ptr<SceneObject> pSceneObject1 = std::make_shared<SceneObject>();
	//std::shared_ptr<TextureComponent> pTexture{std::make_shared<TextureComponent>("background.jpg")};
	//pSceneObject1->AddComponent(pTexture);

	//std::shared_ptr<SceneObject> pSceneObject2 = std::make_shared<SceneObject>();
	//std::shared_ptr<Font> font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//std::shared_ptr<TextComponent> pText{ std::make_shared<TextComponent>("Programming 4 Assignment", font) };
	//pSceneObject2->AddComponent(pText);
	//pSceneObject1->AddChild(pSceneObject2);

	//pSceneObject1->GetTransform()->Translate(200.0f, 0.0f, 0.0f);

	//auto& inputManager = InputManager::GetInstance();
	//inputManager.AddInput("PressA", std::shared_ptr<Input>(std::make_shared<Input>(Input::PressedState::ButtonPressed, XINPUT_GAMEPAD_A)));


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
