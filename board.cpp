#include "board.h"
#include "util.h"

#include <iostream>

Board::Board()
	: m_matrix(HEIGHT, std::vector<unsigned int>(WIDTH))
{
	std::cout << "board generated" << std::endl;
	print_board();
}

Board::~Board()
{
}

unsigned int Board::get_matrix(int width, int row, int col)
{
	return m_matrix[row][col];
}

uint_arr Board::get_matrix_arr() const
{
	return m_matrix;
}

void Board::set_matrix(int width, int row, int col, unsigned int value)
{
	m_matrix[row][col] = value;
}

void::Board::print_board()
{
	for (int row = 0; row < m_matrix.size(); row++)
	{
		for (int col = 0; col < m_matrix[row].size(); col++)
		{
			std::cout << m_matrix[row][col] << ", ";
		}
		std::cout << std::endl;
	}
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
}

void Board::draw_cell(SDL_Renderer* renderer, int row, int col, unsigned int value, const int width, const int height)
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

void Board::draw_board(SDL_Renderer* renderer, const int width, const int height)
{
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			unsigned int value = get_matrix(width, row, col);

			if (value > 0)
			{
				draw_cell(renderer, row, col, value, width, height);
			}
			
		}
	}
}