#include "Game.h"

#include "TextureManager.h"
#include "InputHandler.h"
#include "MainMenuState.h"
#include "GameObjectFactory.h"
#include "MenuButton.h"
#include "AnimatedGraphic.h"
#include "Player.h"
#include "ScrollingBackground.h"
#include "SoundManager.h"
// #include "RoofTurret.h"
// #include "ShotGlider.h"
// #include "Eskeletor.h"
// #include "Level1Boss.h"
#include "GameOverState.h"
#include <iostream>

typedef TextureManager TextureMgr;

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
				SDL_SetRenderDrawColor(mp_renderer, 0x00, 0x00, 0x00, 0x00);
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
	
	m_game_width = width;
	m_game_height = height;
	
	mb_running = true;

	InputHandler::get_instance()->init_joysticks();
	TextureMgr::get_instance()->load("assets/volt.png", "volt_run", Game::get_instance()->get_renderer());
	
	GameObjectFactory::get_instance()->register_type("MenuButton", new MenuButtonCreator());
	GameObjectFactory::get_instance()->register_type("AnimatedGraphic", new AnimatedGraphicCreator());
	GameObjectFactory::get_instance()->register_type("Player", new PlayerCreator());
	// GameObjectFactory::get_instance()->register_type("Enemy", new EnemyCreator());


	m_pgame_state_machine = new GameStateMachine();
	m_pgame_state_machine->change_state(new MainMenuState());
	return true;
}


void Game::render()
{
	/*Clearing the renderer to draw color*/
	SDL_RenderClear(mp_renderer);

	//replaced the two calls to draw [GameObject integration]
	// for (auto go : m_game_objects)
	// 	go->draw();

	//FSM is being used now ;)
	m_pgame_state_machine->render();
	/*Drawing to the screen*/
	SDL_RenderPresent(mp_renderer);
}

void Game::update()
{
	/*to implement*/
	// m_current_frame = int((SDL_GetTicks() / 100) % 6);
	// for (auto go : m_game_objects)
	// 	go->update();

	m_pgame_state_machine->update();
}

void Game::handle_events()
{
	InputHandler::get_instance()->update();
}


void Game::clean()
{
	std::cout << "Cleaning game \n";
	InputHandler::get_instance()->clean();
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

void Game::quit() 
{
	SDL_Quit();
}


void Game::set_current_level(int current_level)
{
	m_current_level = current_level;
	m_pgame_state_machine->change_state(new GameOverState());
	mb_level_complete = false;
}