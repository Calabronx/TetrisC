#include "input.h"
#include "util.h"

#include <iostream>

InputManager::InputManager()
{
}

int InputManager::input_keyboard(InputState* input, TetrominoShape* tetromino)
{
	SDL_Event event;
	int key = 0;

	while (SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_KEYDOWN:
				m_key_map[event.key.keysym.sym] = true;
				if (m_key_map[SDLK_LEFT])
				{
					input->left++;
					key = LEFT;
				}

				if (m_key_map[SDLK_RIGHT])
				{
					input->right++;
					key = RIGHT;
				}

				if (m_key_map[SDLK_UP])
				{
					input->up++;
					key = UP;
				}
				
				if (m_key_map[SDLK_DOWN])
				{
					input->down++;
					key = DOWN;
				}

				if (m_key_map[SDLK_ESCAPE])
				{
					input->esc++;
					key = ESCAPE;
				}

				if (m_key_map[SDLK_SPACE])
				{
					input->back++;
					key = BACKSPACE;
					std::cout << "BACKSPACE" << std::endl;
				}
				break;

			case SDL_KEYUP:
				 m_key_map[event.key.keysym.sym] = false;
				 break;

		}
	}


	return key;
}