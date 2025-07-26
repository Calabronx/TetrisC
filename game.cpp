#include "game.h"
#include "colors.h"
#include "data.h"

#include <random>
#include <iostream>


bool is_merged = false;
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
	game.phase = GAME_PHASE_PLAY;

	for ( int i = 0; i < HEIGHT ;i++)
	{
		game.lines.push_back(0);
	}

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
	input_game(game, input, board, &game->tetromino);
	render(game, board);
}

void Game::update_game_line(GameState* game, Board* board)
{
	if (game->time >= game->highlight_end_time)
	{
		check_lines_to_clear(game, board, &game->lines);
		game->line_count += game->pending_line_count;
		game->phase = GAME_PHASE_PLAY;
	}
}

void Game::input_game(GameState* game, InputManager* input, Board* board, TetrominoShape* tetromino)
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

	if (input_state.down > 0)
	{
		std::cout << "move down" << std::endl;
		piece.offset_row++;

		std::cout << "touch " << piece.offset_row << std::endl;
		if (!check_piece_valid(game, &piece, board, WIDTH, HEIGHT))
		{
			piece = tetromino->get_state_of_piece();
			soft_drop(game, board, &piece);
		}
	}

	if(game->time - game->last_time >= DROP_TIME)
	{
		piece = tetromino->get_state_of_piece();
		soft_drop(game, board, &piece);
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

	if (input_state.back > 0)
	{
		while(soft_drop(game, board, &piece));
		game->tetromino.set_state_of_piece(piece);
	}

	game->pending_line_count = find_lines(board, WIDTH, HEIGHT, &game->lines);
	if (game->pending_line_count > 0)
	{
		game->phase = GAME_PHASE_LINE;
		game->highlight_end_time = game->time + 0.5f;
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
				is_merged = false;
			}
		}
	}
}

bool Game::soft_drop(GameState* game, Board* board, PieceState* piece)
{
	game->last_time = game->time;
	++piece->offset_row;

	if (!check_piece_valid(game, piece, board, WIDTH, HEIGHT))
	{
			merge_piece(game, board);
			spawn_piece(game);
			std::cout << "soft_drop() mergeo pieza" << std::endl;

			return false;
		
	}

	return true;
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
					std::cout << "collision left" << std::endl;
					return false;
				}

				if (board_row >= height) // el valor en realidad deberia ser el height, pero es mayor al final del tablero
				{
					return false;
				}

				if (board_col < 0)
				{
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

void Game::check_lines_to_clear(GameState* game, Board* board, const std::vector<unsigned int>* lines)
{
	int src_row = HEIGHT - 1;
	for (int dst_row = src_row; dst_row >= 0; --dst_row)
	{
		while (src_row > 0 && (*lines)[src_row])
		{
			--src_row;
		}

		src_row = board->clear_lines(src_row, dst_row);
	}
}

int Game::get_row_filled(Board* board, int width, int row)
{
	for (int col = 0; col < width; ++col)
	{
		if(!board->get_matrix(width, row, col))
		{
			return 0;
		}
	}
	return 1;
}

int Game::find_lines(Board *board, int width, int height, std::vector<unsigned int>* lines_out)
{
	int count = 0;
	for (int row = 0; row < height; row++)
	{
		unsigned int filled = get_row_filled(board, width, row);

		(*lines_out)[row] = filled;
		count += filled;
	}

	return count;
}

void Game::start_game(GameState* game, InputManager* input, Board *board)
{
	bool exit = false;
	std::cout << "game started running" << std::endl;

	while (!exit)
	{
		game->time = SDL_GetTicks() / 1000.0f;

		switch(game->phase)
		{
			case GAME_PHASE_PLAY:
				update(game, board, input);
				break;
			case GAME_PHASE_LINE:
				update_game_line(game, board);
				break;
		}

		if (game->phase == GAME_PHASE_OVER)
		{
			exit = true;
		}
	}
}

Game::GameState::GameState()
{
}
