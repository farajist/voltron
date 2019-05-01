#include "GameOverState.h"

#include "MainMenuState.h"
#include "PlayState.h"
#include "TextureManager.h"
#include "AnimatedGraphic.h"
#include "Game.h"
#include "MenuButton.h"
#include "InputHandler.h"
#include "StateParser.h"

const std::string GameOverState::s_game_over_id = "GAMEOVER";

void GameOverState::update()
{
	for (auto &go : m_game_objects)
	{
		go->update();
	}
}


void GameOverState::render()
{
	for (auto &go : m_game_objects)
	{
		go->draw();
	}
}

bool GameOverState::on_enter()
{
	
	StateParser parser;
	parser.parse_state("test.xml", s_game_over_id, &m_game_objects, &m_texture_ids);
	
	m_callbacks.push_back(0);
	m_callbacks.push_back(s_game_over_to_main);
	m_callbacks.push_back(s_restart_play);
	
	set_callbacks(m_callbacks);

	std::cout << "Entering GameOverState\n";
	return true;
}


bool GameOverState::on_exit()
{

	// m_exiting = true;
	for(auto& go : m_game_objects) 
	{
		go->clean();
	}
	m_game_objects.clear();
	//bullshit right ?
	for (auto& ti : m_texture_ids)
		TextureMgr::get_instance()->clear_from_texture_map(ti);

	std::cout << "Exiting MenuState\n";
	return true;
}

void GameOverState::s_game_over_to_main()
{
	Game::get_instance()->get_state_machine()->change_state(new MainMenuState());
}

void GameOverState::s_restart_play()
{
	Game::get_instance()->get_state_machine()->change_state(new PlayState());
}


void GameOverState::set_callbacks(const std::vector<Callback>& cbcks)
{
	//same as always : now in each game state a part
	for (auto &go : m_game_objects)
	{
		//if object is menubutton give a callback
		if (dynamic_cast<MenuButton*>(go))
		{
			MenuButton* btn = dynamic_cast<MenuButton*>(go);
			btn->set_callback(cbcks[btn->get_callback_id()]);
		}
	}
}