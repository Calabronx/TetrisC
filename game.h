#ifndef GAME_H
#define GAME_H

#include "util.h"
#include "board.h"
#include "tetromino.h"
#include "input.h"

#include <SDL2/SDL.h>

#include <vector>

enum GamePhase
{
	GAME_PHASE_STARTED,
	GAME_PHASE_OVER
};

struct GameState
{
	GamePhase phase;
	Tetromino tetro_player;
};

class Game {
	public:
		Game();
		~Game();
	private:
		void init();
		void update();
		void render();
		int  input();

		//in game methods
		void spawn_piece();
		void draw_piece(SDL_Renderer* renderer, PieceState* piece, int row, int col, unsigned int value, const int width, const int height);
		void draw_tetromino(SDL_Renderer* renderer, int x, int y, const int width, const int height);
		bool check_piece_valid(PieceState* piece);

		void render_board(SDL_Renderer *renderer);
	public:
		void run();

	private:
		Board			*m_board;
		InputManager	*m_input;
		Tetromino		*m_player;

		SDL_Window 		*m_window;
		SDL_Renderer 	*m_renderer;
		SDL_Surface 	*m_surface;


	};


#endif