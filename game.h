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
		void update(GameState* game, Board* board ,InputManager* input);
		void render(GameState* game, Board* board);
		void input_management(GameState* game, InputManager* input, Board* board, TetrominoShape* tetromino);

		//in game methods
		void spawn_piece(GameState* game);
		void merge_piece(GameState* game, Board* board);
		bool soft_drop(GameState* game, Board* board);
		bool check_piece_valid(GameState* game, PieceState* piece, Board *board, int width, int height);

		void render_board(SDL_Renderer *renderer, Board* board);
		void start_game(GameState* game, InputManager* input, Board *board);

	private:
		SDL_Window 		*m_window;
		SDL_Renderer 	*m_renderer;
		SDL_Surface 	*m_surface;
	};


#endif