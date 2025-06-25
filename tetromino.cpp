#include "tetromino.h"

TetrominoShape::TetrominoShape(const Tetromino& tetromino)
{
	m_piece_state = {};
	m_tetromino = &tetromino;
}

TetrominoShape::TetrominoShape()
{
}

const unsigned int TetrominoShape::get_tetromino(int row, int col, int rotation) const
{
	int side = m_tetromino->side;

	const uint_arr matrix = *m_tetromino->data;

	switch(rotation)
	{
		case 0:
			return matrix[row][col];
		case 1:
			return matrix[side - col - 1][row];
		case 2:
			return matrix[side - row - 1][side - col - 1];
		case 3:
			return matrix[col][side - row - 1];
	}
	return 0;
}

uint_arr TetrominoShape::get_matrix() const
{
	return *m_tetromino->data;
}

int TetrominoShape::getSide() const
{
	return m_tetromino->side;
}

void TetrominoShape::set_position(Vector2 position)
{
	m_position = position;
}

Vector2 TetrominoShape::get_position() const
{
	return m_position;
}

PieceState TetrominoShape::get_state_of_piece() const
{
	return m_piece_state;
}

void TetrominoShape::set_state_of_piece(PieceState piece_state)
{
	m_piece_state = piece_state;
}

void TetrominoShape::draw_piece(SDL_Renderer* renderer, PieceState* piece, int row, int col, unsigned int value, const int width, const int height)
{
	Color base_color = BASE_COLORS[value];
	Color light_color = LIGHT_COLORS[value];
	Color dark_color = DARK_COLORS[value];

	int edge = GRID_SIZE / 8;

	int x = col * GRID_SIZE;
	int y = row * GRID_SIZE;

	fill_rect(renderer, x, y, width, height, dark_color);
	fill_rect(renderer, x + edge, y, GRID_SIZE - edge, GRID_SIZE - edge, light_color);
	fill_rect(renderer, x + edge, y + edge, GRID_SIZE - edge * 2, GRID_SIZE - edge * 2, base_color);
}

void TetrominoShape::draw_tetromino(SDL_Renderer* renderer, const int width, const int height)
{
	for (int row = 0; row < m_tetromino->side; row++)
	{
		for (int col = 0; col < m_tetromino->side; col++)
		{
			unsigned int value = get_tetromino(row, col, m_piece_state.rotation);
			if (value > 0)
			{
				draw_piece(renderer, &m_piece_state, row + m_piece_state.offset_row, col + m_piece_state.offset_col, value, width, height);
			}
		}
	}
}


