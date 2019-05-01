#include "PauseState.h"

#include "PauseState.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "InputHandler.h"
#include "StateParser.h"

const std::string PauseState::s_pause_id = "PAUSE";

void PauseState::update()
{
	for (auto &go : m_game_objects)
	{
		go->update();
	}
}


void PauseState::render()
{
	//same as always : now in each game state a part
	for (auto &go : m_game_objects)
	{
		go->draw();
	}
}

bool PauseState::on_enter()
{
	
	StateParser parser;
	parser.parse_state("test.xml", s_pause_id, &m_game_objects, &m_texture_ids);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_pause_to_main);
	m_callbacks.push_back(s_resume_play);
	
	set_callbacks(m_callbacks);

	std::cout << "Entering PauseState\n";
	return true;
}


bool PauseState::on_exit()
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

	std::cout << "Exiting PauseState\n";
	return true;
}



void PauseState::s_pause_to_main()
{
	Game::get_instance()->get_state_machine()->change_state(new MainMenuState());
}

void PauseState::s_resume_play()
{
	Game::get_instance()->get_state_machine()->pop_state();
}


void PauseState::set_callbacks(const std::vector<Callback>& cbcks)
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