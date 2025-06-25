#ifndef GAME_H
#define GAME_H

#include "util.h"
#include "board.h"
#include "tetromino.h"
#include "input.h"

#include <SDL2/SDL.h>

#include <vector>

class Game {

	enum GamePhase
	{
		GAME_PHASE_STARTED,
		GAME_PHASE_OVER
	};

	struct GameState
	{
		GamePhase 		phase;
		TetrominoShape 	tetromino; // player tetromino
		InputState 		input;

		GameState();

	};

	public:
		Game();
		~Game();
	private:
		void init();
		void update(GameState* game);
		void render(GameState* game);
		void input_key(GameState* game, InputManager* input, TetrominoShape* tetromino);

		//in game methods
		void spawn_piece(GameState* game);
		//bool check_piece_valid(PieceState* piece);

		void render_board(SDL_Renderer *renderer);
		void start_game(GameState* game, InputManager* input, Board *board);

	private:
		// Tetromino		*m_player;

		SDL_Window 		*m_window;
		SDL_Renderer 	*m_renderer;
		SDL_Surface 	*m_surface;
	};


#endif