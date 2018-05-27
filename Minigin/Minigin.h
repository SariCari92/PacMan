#pragma once

struct SDL_Window;

namespace dae
{
	class Minigin
	{
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();

		static int GetSDL_WindowWidth();
		static int GetSDL_WindowHeight();
	private:
		const int msPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		static int m_WindowWidth;
		static int m_WindowHeight;
		SDL_Window* window{};
	};
}