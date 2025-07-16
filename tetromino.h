#ifndef TETROMINO_H
#define TETROMINO_H

#include <vector>
#include <SDL2/SDL.h>

#include "data.h"
#include "util.h"

struct PieceState
{
	unsigned int 			tetromino_index;
	int 					offset_row;
	int 					offset_col;
	int 					rotation;
};

class TetrominoShape
{
	public:
																					TetrominoShape(const Tetromino& tetromino);
																					TetrominoShape();
	public:
		const unsigned int 		get_tetromino(int row, int col, int rotation) const;
		uint_arr 				get_matrix() const;
		int 					get_side() const;
		void					set_position(Vector2 position);
		Vector2					get_position() const;
		PieceState				get_state_of_piece() const;
		void 					set_state_of_piece(PieceState piece_state);


		void 						draw_piece(SDL_Renderer* renderer, PieceState* piece, int row, int col, unsigned int value, const int width, const int height);
		void 						draw_tetromino(SDL_Renderer* renderer, const int width, const int height);

	private:
		PieceState							m_piece_state;
		Vector2								m_position;
		const Tetromino*					m_tetromino;
};

#endif