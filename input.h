#ifndef INPUT_H
#define INPUT_H

#include <map>
#include <SDL2/SDL.h>

#include "tetromino.h"

struct InputState
{
	unsigned int left;
	unsigned int right;
	unsigned int down;
	unsigned int up;
	unsigned int esc;
};

class InputManager {

public:
	InputManager();
	~InputManager();

	int input_keyboard(PieceState* piece);

	private:
		std::map<SDL_Keycode, bool> m_key_map;
};

#endif 