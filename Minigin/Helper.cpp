#include "MiniginPCH.h"
#include "Helper.h"
#include "SDL_rect.h"
#include "Renderer.h"

void DrawRectangle(int x, int y, int width, int height, SDL_Color color)
{
	SDL_Rect rect{};
	rect.x = x;
	rect.y = y;
	rect.w = width;
	rect.h = height;
	const auto &renderer = dae::Renderer::GetInstance().GetSDLRenderer();

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawRect(renderer, &rect);
}
void DrawRectangle(const SDL_Rect *pRect, SDL_Color color)
{
	const auto &renderer = dae::Renderer::GetInstance().GetSDLRenderer();
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawRect(renderer, pRect);
}

void DrawFilledRectangle(int x, int y, int width, int height, SDL_Color color)
{
	SDL_Rect rect{};
	rect.x = x;
	rect.y = y;
	rect.w = width;
	rect.h = height;

	const auto &renderer = dae::Renderer::GetInstance().GetSDLRenderer();
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);
}
void DrawFilledRectangle(const SDL_Rect *pRect, SDL_Color color)
{
	const auto &renderer = dae::Renderer::GetInstance().GetSDLRenderer();
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, pRect);
}

SDL_Color CreateSDLColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_Color color;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;

	return color;
}

SDL_Rect CreateSDLRectangle(int x, int y, int width, int height)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = width;
	rect.h = height;

	return rect;
}