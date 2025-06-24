#ifndef TETROMINO_H
#define TETROMINO_H

#include <vector>

#include "data.h"
#include "util.h"

struct PieceState
{
		unsigned int 	tetrino_index;
		int 			offset_row;
		int 			offset_col;
		int 			rotation;
};

class Tetromino
{
	public:
					Tetromino(const uint_arr &matrix, int side);
					~Tetromino();

	public:
		unsigned int 	get_tetromino(int row, int col, int rotation);
		uint_arr 		get_matrix();
		int 			getSide() const;
		void			set_position(Vector2 position);
		Vector2			get_position() const;
		PieceState*		get_state_of_piece() const;

	private:
		std::vector<std::vector<unsigned int>> 				 m_matrix;
		int 												 m_side;
		PieceState*											 m_piece_state;
		Vector2												 m_position;
};

#endif