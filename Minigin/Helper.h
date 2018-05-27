#pragma once
#include<SDL_render.h>

struct SDL_Rect;

void DrawRectangle(int x, int y, int width, int height, SDL_Color color);
void DrawRectangle(const SDL_Rect *pRect, SDL_Color color);

void DrawFilledRectangle(int x, int y, int width, int height, SDL_Color color);
void DrawFilledRectangle(const SDL_Rect *pRect, SDL_Color color);

SDL_Color CreateSDLColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
SDL_Rect CreateSDLRectangle(int x, int y, int width, int height);
