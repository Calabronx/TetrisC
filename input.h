#ifndef INPUT_H
#define INPUT_H

#include <map>
#include <SDL2/SDL.h>

#include "tetromino.h"

#include "util.h"

class InputManager {

public:
	InputManager();
	// ~InputManager();

	int input_keyboard(InputState* input, TetrominoShape* tetromino);// VECTOR

	private:
		std::map<SDL_Keycode, bool> m_key_map;
};

#endif 