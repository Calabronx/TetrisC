#include "input.h"
#include "util.h"



#include <iostream>

InputManager::InputManager()
{
}

int InputManager::input_keyboard(PieceState* piece)
{
	SDL_Event event;
	int key = 0;

	InputState input = {};

	while (SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_KEYDOWN:
				m_key_map[event.key.keysym.sym] = true;
				if (m_key_map[SDLK_LEFT])
				{
					input.left++;
					key = LEFT;
				}

				if (m_key_map[SDLK_RIGHT])
				{
					input.right++;
					key = RIGHT;
				}

				if (m_key_map[SDLK_UP])
				{
					input.up++;
					key = UP;
				}
				
				if (m_key_map[SDLK_DOWN])
				{
					input.down++;
					key = DOWN;
				}

				if (m_key_map[SDLK_ESCAPE])
				{
					input.esc++;
					key = ESCAPE;
				}


				if (input.left > 0)
				{
					std::cout << "move left" << std::endl;
					piece->offset_col--;
				}

				if (input.right > 0)
				{
					std::cout << "move right" << std::endl;
					piece->offset_col++;
				}

				if (input.down > 0)
				{
					std::cout << "move down" << std::endl;
					piece->offset_row++;
				}

				if (input.esc > 0)
				{
					std::cout << "exit" << std::endl;
				}

				if (input.up > 0)
				{
					piece->rotation = (piece->rotation + 1) % 4;
				}

				break;

			case SDL_KEYUP:
				 m_key_map[event.key.keysym.sym] = false;
				 break;

		}
	}


	return key;
}