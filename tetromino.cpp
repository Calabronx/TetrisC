#include "tetromino.h"

Tetromino::Tetromino(const uint_arr &matrix, int side)
{
	m_matrix = matrix;
	m_side = side;
	m_piece_state = new PieceState();
	m_position = {};
}

unsigned int Tetromino::get_tetromino(int row, int col, int rotation)
{
	int side = m_side;

	switch(rotation)
	{
		case 0:
			return m_matrix[row][col];
		case 1:
			return m_matrix[side - col - 1][row];
		case 2:
			return m_matrix[side - row - 1][side - col - 1];
		case 3:
			return m_matrix[col][side - row - 1];
	}
	return 0;
}

uint_arr Tetromino::get_matrix()
{
	return m_matrix;
}

int Tetromino::getSide() const
{
	return m_side;
}

void Tetromino::set_position(Vector2 position)
{
	m_position = position;
}

Vector2 Tetromino::get_position() const
{
	return m_position;
}

PieceState* Tetromino::get_state_of_piece() const
{
	return m_piece_state;
}



