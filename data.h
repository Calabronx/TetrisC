#ifndef DATA_H
#define DATA_H

#include <vector>

typedef std::vector<std::vector<unsigned int>>  uint_arr;
struct Tetromino
{
	const uint_arr 		*data;
	int 				side;
};

// tetrominos matrices
typedef std::vector<std::vector<std::vector<Tetromino>>> tetrominos_table;


inline Tetromino tetromino(const uint_arr* matrix, int side)
{
	Tetromino tetro = {};
	tetro.data = matrix;
	tetro.side = side;
	return tetro;
}

const uint_arr TETROMINO_1 = {
	{0, 0, 0, 0},
	{1, 1, 1, 1},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
};

const uint_arr TETROMINO_2 = {
	{2, 2},
	{2, 2}
};

const uint_arr TETROMINO_3 = {
	{0, 0, 0},
	{3, 3, 3},
	{0, 3, 0}
};

const uint_arr TETROMINO_4 = {
	{0, 4, 4},
	{4, 4, 0},
	{0, 0, 0}
};

const uint_arr TETROMINO_5 = {
	{5, 5, 0},
	{0, 5, 5},
	{0, 0, 0}
};

const uint_arr TETROMINO_6 = {
	{6, 0, 0},
	{6, 6, 6},
	{0, 0, 0}
};

const uint_arr TETROMINO_7 = {
	{0, 0, 7},
	{7, 7, 7},
	{0, 0, 0}
};


const std::vector<Tetromino> TETROMINOS = {
	tetromino(&TETROMINO_1, 4),
	tetromino(&TETROMINO_2, 2),
	tetromino(&TETROMINO_3, 3),
	tetromino(&TETROMINO_4, 3),
	tetromino(&TETROMINO_5, 3),
	tetromino(&TETROMINO_6, 3),
	tetromino(&TETROMINO_7, 3),
};
#endif