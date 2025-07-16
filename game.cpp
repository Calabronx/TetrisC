#include "game.h"
#include "colors.h"
#include "data.h"

#include <random>
#include <iostream>

Game::Game()
{
	init();
}

Game::~Game()
{

}

void Game::init()
{
	GameState game;
	game.input = {};
	Board board = {};
	InputManager input = {};
	game.phase = GAME_PHASE_STARTED;

	srand(time(NULL));

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Failed to initialize the window\n";
		return;
	}

	m_window = SDL_CreateWindow("Tetris",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT, 0);

	if (m_window == nullptr)
	{
		std::cout << "Failed to create the window\n";
		return;
	}

	if (!m_window)
	{
		SDL_Log("Window pointer is null!");
		return;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
	if (!m_renderer) {
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return;
	}

	m_surface = SDL_GetWindowSurface(m_window);

	if (m_surface == nullptr)
	{
		std::cout << "Failed to get the surface from the window\n";
		return;
	}

	spawn_piece(&game);

	start_game(&game, &input, &board);

}

void Game::update(GameState* game, Board* board, InputManager* input)
{
	input_management(game, input, board, &game->tetromino);
	render(game, board);
}

void Game::input_management(GameState* game, InputManager* input, Board* board, TetrominoShape* tetromino)
{
	InputState input_state = game->input;
	PieceState piece = tetromino->get_state_of_piece();

	input->input_keyboard(&input_state, tetromino);

	if (input_state.left > 0)
	{
		std::cout << "move left" << std::endl;
		piece.offset_col--;
	}

	if (input_state.right > 0)
	{
		std::cout << "move right" << std::endl;
		piece.offset_col++;
	}

	if (input_state.down > 0 && input_state.right == 0 && input_state.left == 0)
	{
		std::cout << "move down" << std::endl;
		piece.offset_row++;

		std::cout << "touch " << piece.offset_row << std::endl;
		if (!check_piece_valid(game, &piece, board, WIDTH, HEIGHT))
		{
			merge_piece(game, board);
			spawn_piece(game);
			soft_drop(game, board);
		}
	}

	if (input_state.esc > 0)
	{
		std::cout << "exit" << std::endl;
		game->phase = GAME_PHASE_OVER;
	}

	if (input_state.up > 0)
	{
		piece.rotation = (piece.rotation + 1) % 4;
	}

	if(check_piece_valid(game, &piece, board, WIDTH, HEIGHT))
	{
		game->tetromino.set_state_of_piece(piece);
	}
}

void Game::render_board(SDL_Renderer* renderer, Board* board)
{
	SDL_SetRenderDrawColor(renderer, BARELY_BLACK.r, BARELY_BLACK.g, BARELY_BLACK.b, BARELY_BLACK.a);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, DARK_GREY.r, DARK_GREY.g, DARK_GREY.b, DARK_GREY.a);

	// for (int x = 0; x < 1 + WIDTH * CELL_SIZE; x += CELL_SIZE)
	// {
	// 	SDL_RenderDrawLine(renderer, x, 0, x, SCREEN_HEIGHT);
	// }

	// for (int y = 0; y < HEIGHT * CELL_SIZE; y += CELL_SIZE)
	// {
	// 	SDL_RenderDrawLine(renderer, 0, y, SCREEN_WIDTH, y);
	// }

	// SDL_RenderPresent(renderer);

	board->draw_board(renderer, WIDTH, HEIGHT);

}

void Game::render(GameState* game, Board* board)
{
	SDL_RenderClear(m_renderer);

	render_board(m_renderer, board);

	game->tetromino.draw_tetromino(m_renderer, CELL_SIZE, CELL_SIZE);

	SDL_SetRenderDrawColor(m_renderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a);

	SDL_RenderPresent(m_renderer);
}

void Game::spawn_piece(GameState* game)
{
	// game
	int index = 1 + rand() % TETROMINOS.size() - 1;
	game->tetromino = TetrominoShape(TETROMINOS[index]);

	PieceState piece;
	piece.offset_col = WIDTH / 2;
	piece.offset_row = 0;
	piece.rotation = 0;
	piece.tetromino_index = index;
	game->tetromino.set_state_of_piece(piece);
}

void Game::merge_piece(GameState* game, Board* board)
{
	const TetrominoShape* tetromino = &game->tetromino;
	PieceState piece = tetromino->get_state_of_piece();
	for (int row = 0; row < tetromino->get_side(); row++)
	{
		for (int col = 0; col < tetromino->get_side(); col++)
		{
			unsigned int value = tetromino->get_tetromino(row, col, piece.rotation);

			if (value > 0)
			{
				int border_row = piece.offset_row + row;
				int border_col = piece.offset_col + col;

				board->set_matrix(WIDTH, border_row, border_col, value);

				board->print_board();
			}
		}
	}
}

bool Game::soft_drop(GameState* game, Board* board)
{
	return false;
}

bool Game::check_piece_valid(GameState* game, PieceState* piece, Board *board, int width, int height)
{
	const TetrominoShape *tetromino = &game->tetromino;
	int side = tetromino->get_side();
	for (int row = 0; row < side; row++)
	{
		for (int col = 0; col < side; col++)
		{
			unsigned int value = tetromino->get_tetromino(row, col, piece->rotation);

			if (value > 0)
			{
				int board_row = piece->offset_row + row;
				int board_col = piece->offset_col + col;

				if (board_row < 0)
				{
					return false;
				}

				if (board_row >= height) // el valor en realidad deberia ser el height, pero es mayor al final del tablero
				{
					std::cout << "collision down" << std::endl;
					return false;
				}

				if (board_col < 0)
				{
					std::cout << "collision left" << std::endl;
					return false;
				}

				if (board_col >= width)
				{
					return false;
				}

				if (board->get_matrix(width, board_row, board_col))
				{
					return false;
				}
			}
		}
	}

	return true;
}

void Game::start_game(GameState* game, InputManager* input, Board *board)
{
	bool exit = false;
	std::cout << "game started running" << std::endl;

	while (!exit)
	{
		update(game, board, input);

		if (game->phase == GAME_PHASE_OVER)
		{
			exit = true;
		}
	}
}

Game::GameState::GameState()
{
}
