#include "game.h"
#include "colors.h"

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

	m_board = new Board();
	m_input = new InputManager();

	spawn_piece();
}

void Game::update()
{
	render();
}

int Game::input()
{
	PieceState* piece = m_player->get_state_of_piece();
	int key = m_input->input_keyboard(piece);
	// solo para debuggear despues se elimina
	if (key != 0)
	{
		std:: cout << "key: " <<key << std::endl;
	}

	return key;
}

void Game::render_board(SDL_Renderer *renderer)
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

void Game::draw_piece(SDL_Renderer* renderer, PieceState* piece, int row, int col, unsigned int value, const int width, const int height)
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

void Game::draw_tetromino(SDL_Renderer* renderer, int x, int y, const int width, const int height)
{
	std::vector<std::vector<unsigned int>> tetromino = m_player->get_matrix();
	int side = m_player->getSide();
	PieceState* piece = m_player->get_state_of_piece();

	for (int row = 0; row < side; row++)
	{
		for (int col = 0; col < side; col++)
		{
			unsigned int value = m_player->get_tetromino(row, col, piece->rotation);
			if (value > 0)
			{
				draw_piece(renderer, piece, row + piece->offset_row, col + piece->offset_col, value, width, height);
			}
		}
	}
}

void Game::render()
{
	SDL_RenderClear(m_renderer);
	
	render_board(m_renderer);
	draw_tetromino(m_renderer, 0, 0, CELL_SIZE, CELL_SIZE);

	SDL_SetRenderDrawColor(m_renderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a);

	SDL_RenderPresent(m_renderer);
}

void Game::spawn_piece()
{
	m_player = new Tetromino(TETROMINO_1, 4);
}

void Game::run()
{
	bool exit = false;
	std::cout << "game started running" << std::endl;

	while(!exit)
	{
		update();
		int key = input();

		if (key == ESCAPE)
		{
			exit = true;
		}
	}
}

