#ifndef BOARD_H
#define BOARD_H

#include "data.h"
#include <SDL2/SDL.h>

class Board
{
	public:
		Board();
		~Board();

	public:
		uint_arr 			get_matrix_arr() const;
		unsigned int 		get_matrix(int width, int row, int col);
		void 				set_matrix(int width, int row, int col, unsigned int value);
		int 				clear_lines(int src_row, int dst_row);
		void 				print_board();
		void				draw_cell(SDL_Renderer* renderer, int row, int col, unsigned int value, const int width, const int height);
		void				draw_board(SDL_Renderer* renderer, const int width, const int height);
	private:
		uint_arr 		m_matrix;
};

#endif
