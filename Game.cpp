#include "Game.h"

Game* Game::sp_instance = nullptr;

bool Game::init(std::string title, int xpos, int ypos, int width,
			int height, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		std::cout << "SDL initialization success \n";
		mp_window = SDL_CreateWindow (title.c_str(), xpos, ypos,
			width, height, flags);

		if (mp_window != NULL)
		{
			std::cout << "SDLWindow creation success \n";
			mp_renderer = SDL_CreateRenderer(mp_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (mp_renderer != NULL)
			{
				std::cout << "SDLRenderer creation success \n";
				SDL_SetRenderDrawColor(mp_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			} 
			else 
			{
				std::cout << "SDLRenderer creation failure \n";
				return false;
			}
		}
		else 
		{
			std::cout << "SDLWindow creation failure\n";
			return false;
		}
	}
	else
	{
		std::cout << "SDL initialization failure\n";
		return false;
	}
	/*Everything succeded successfully */
	std::cout << "initialization succeeded !\n";
	mb_running = true;
	
	TextureMgr::get_instance()->load("assets/volt.png", "volt_run", Game::get_instance()->get_renderer());

	// m_player = new Player();
	// m_go = new GameObject();
	// m_en = new Enemy();

	// m_player->load(395, 395, 140, 193, "volt_run");
	// m_go->load(200, 200, 140, 193, "volt_run");
	 // m_en->load(0, 0, 140, 193, "volt_run");

	m_game_objects.push_back(new Player(new LoaderParams(395, 395, 140, 193, "volt_run")));
	// m_game_objects.push_back(m_go);
	m_game_objects.push_back(new Enemy(new LoaderParams(0, 0, 140, 193, "volt_run")));
	

	return true;
}


void Game::render()
{
	/*Clearing the renderer to draw color*/
	SDL_RenderClear(mp_renderer);

	//replaced the two calls to draw [GameObject integration]
	for (auto go : m_game_objects)
		go->draw();

	/*Drawing to the screen*/
	SDL_RenderPresent(mp_renderer);
}

void Game::update()
{
	/*to implement*/
	// m_current_frame = int((SDL_GetTicks() / 100) % 6);
	for (auto go : m_game_objects)
		go->update();
}

void Game::handle_events()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT :
				mb_running = false;
				break;

			default : break;
		}
	}
}


void Game::clean()
{
	std::cout << "Cleaning game \n";
	SDL_DestroyWindow(mp_window);
	SDL_DestroyRenderer(mp_renderer);
	SDL_Quit();
}

Game* Game::get_instance() 
{
	if (sp_instance == nullptr)
	{
		sp_instance = new Game();
		return sp_instance;
	}
	return sp_instance;
}

