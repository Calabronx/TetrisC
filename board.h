#ifndef BOARD_H
#define BOARD_H

#include "data.h"

class Board
{
	public:
		Board();
		~Board();

	public:
		uint_arr 			get_matrix_arr() const;
	private:

		unsigned int 		get_matrix(int width, int row, int col);
		void 				set_matrix(int width, int row, int col, unsigned int value);

		

	private:
		uint_arr 		m_matrix;
};

#endif
