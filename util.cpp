#include "util.h"

#include <SDL2/SDL.h>

void fill_rect(SDL_Renderer* renderer, int x, int y, const int width, const int height, Color color)
{
	SDL_Rect rect;
	rect.x  = x;
	rect.y  = y;
	rect.w  = width;
	rect.h  = height;

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderDrawRect(renderer, &rect);
}