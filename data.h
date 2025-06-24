#ifndef DATA_H
#define DATA_H

#include <vector>

// tetrominos matrices
typedef std::vector<std::vector<unsigned int>> uint_arr;
typedef std::vector<std::vector<std::vector<unsigned int>>> uint_arr_tetrominos;

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


const uint_arr_tetrominos TETROMINOS = {
	TETROMINO_1,
	TETROMINO_2,
	TETROMINO_3,
	TETROMINO_4,
	TETROMINO_5,
	TETROMINO_6,
	TETROMINO_7
};
#endif