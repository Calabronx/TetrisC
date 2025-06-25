#include "game.h"
#include "colors.h"
#include "data.h"

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
	//game.tetromino = TetrominoShape(TETROMINO_1);
	Board board = {};
	InputManager input = {};
	game.phase = GAME_PHASE_STARTED;

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

void Game::update(GameState* game)
{
	render(game);
}

void Game::input_key(GameState* game, InputManager* input, TetrominoShape* tetromino)
{
	InputState input_state = game->input;
	auto piece = tetromino->get_state_of_piece();

	int key = input->input_keyboard(&input_state, tetromino);

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

	game->tetromino.set_state_of_piece(piece);
}

void Game::render_board(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, BARELY_BLACK.r, BARELY_BLACK.g, BARELY_BLACK.b, BARELY_BLACK.a);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, DARK_GREY.r, DARK_GREY.g, DARK_GREY.b, DARK_GREY.a);

	for (int x = 0; x < 1 + WIDTH * CELL_SIZE; x += CELL_SIZE)
	{
		SDL_RenderDrawLine(renderer, x, 0, x, SCREEN_HEIGHT);
	}

	for (int y = 0; y < HEIGHT * CELL_SIZE; y += CELL_SIZE)
	{
		SDL_RenderDrawLine(renderer, 0, y, SCREEN_WIDTH, y);
	}

	// SDL_RenderPresent(renderer);
}

void Game::render(GameState* game)
{
	SDL_RenderClear(m_renderer);

	render_board(m_renderer);

	game->tetromino.draw_tetromino(m_renderer, CELL_SIZE, CELL_SIZE);

	SDL_SetRenderDrawColor(m_renderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a);

	SDL_RenderPresent(m_renderer);
}

void Game::spawn_piece(GameState* game)
{
	// game
	//m_player = new Tetromino(TETROMINO_1, 4);
	game->tetromino = TetrominoShape(TETROMINOS[0]);
}

void Game::start_game(GameState* game, InputManager* input, Board *board)
{
	bool exit = false;
	std::cout << "game started running" << std::endl;

	while (!exit)
	{
		update(game);
		input_key(game, input, &game->tetromino);

		if (game->phase == GAME_PHASE_OVER)
		{
			exit = true;
		}
	}
}

Game::GameState::GameState()
{
}
