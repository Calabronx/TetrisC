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
		GAME_PHASE_PLAY,
		GAME_PHASE_OVER,
		GAME_PHASE_LINE
	};

	struct GameState
	{
		GamePhase 		phase;
		TetrominoShape 	tetromino; // player tetromino
		InputState 		input;

		int 			pending_line_count;
		int 			line_count;

		std::vector<unsigned int> lines;
		float 			time;
		float 			highlight_end_time;
		float			last_time;

		GameState();

	};

	public:
		Game();
		~Game();
	private:
		void init();
		void update(GameState* game, Board* board ,InputManager* input);
		void update_game_line(GameState* game, Board* board);
		void render(GameState* game, Board* board);
		void input_management(GameState* game, InputManager* input, Board* board, TetrominoShape* tetromino);

		//in game methods
		void spawn_piece(GameState* game);
		void merge_piece(GameState* game, Board* board);
		bool soft_drop(GameState* game, Board* board, PieceState* piece);
		bool check_piece_valid(GameState* game, PieceState* piece, Board *board, int width, int height);
		void check_lines_to_clear(GameState* game, Board* board, const std::vector<unsigned int>* lines);
		void check_line_empty(GameState* game, Board* board);
		int get_row_filled(Board* board, int width, int row);
		int find_lines(Board *board, int width, int height, std::vector<unsigned int>* lines_out);

		void render_board(SDL_Renderer *renderer, Board* board);
		void start_game(GameState* game, InputManager* input, Board *board);

	private:
		SDL_Window 		*m_window;
		SDL_Renderer 	*m_renderer;
		SDL_Surface 	*m_surface;
	};


#endif