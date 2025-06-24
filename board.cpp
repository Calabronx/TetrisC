#include "board.h"
#include "util.h"

#include <iostream>

Board::Board()
	: m_matrix(HEIGHT, std::vector<unsigned int>(WIDTH))
{
	std::cout << "board generated" << std::endl;
	for (int row = 0; row < m_matrix.size(); row++)
	{
		for (int col = 0; col < m_matrix[row].size(); col++)
		{
			std::cout << m_matrix[row][col] << ", ";
		}
		std::cout << std::endl;
	}
}

Board::~Board()
{
}

unsigned int Board::get_matrix(int width, int row, int col)
{
	return m_matrix[row * width][col];
}

uint_arr Board::get_matrix_arr() const
{
	return m_matrix;
}

void Board::set_matrix(int width, int row, int col, unsigned int value)
{
	m_matrix[row * width][col] = value;
}

