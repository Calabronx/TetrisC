#ifndef UTIL_H
#define UTIL_H

#include <SDL2/SDL.h>
#include "colors.h"

const int WIDTH = 10;
const int HEIGHT = 22;
const int GRID_SIZE = 30;
const int CELL_SIZE = 30;
const int SCREEN_WIDTH = 300;
const int SCREEN_HEIGHT = 720;
const int DROP_TIME = 1;

struct Vector2
{
	int x = 0;
	int y = 0;

	Vector2(int _x,int _y)
	{
		_x = x;
		_y = y;
	}

	Vector2()
	{
		x = 0;
		y = 0;
	}
};

struct InputState
{
	unsigned int left;
	unsigned int right;
	unsigned int down;
	unsigned int up;
	unsigned int esc;
	unsigned int back;
};

enum KeyPressed
{
	LEFT 	= 1,
	RIGHT 	= 2,
	UP		= 3,
	DOWN 	= 4,
	ESCAPE 	= 5,
	BACKSPACE = 6
};

void fill_rect(SDL_Renderer* renderer, int x, int y, const int width, const int height, Color color);



#endif 