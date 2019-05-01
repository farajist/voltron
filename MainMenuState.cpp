#include "MainMenuState.h"


#include "PlayState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "InputHandler.h"
#include "StateParser.h"
const std::string MainMenuState::s_menu_id = "MENU";

void MainMenuState::update()
{
	// if (!m_exiting)
	// {
		for (auto &go : m_game_objects)
		{
			go->update();
		}
	// }
}


void MainMenuState::render()
{
	//same as always : now in each game state a part
	for (auto &go : m_game_objects)
	{
		go->draw();
	}
}

bool MainMenuState::on_enter()
{
	
	StateParser parser;
	parser.parse_state("test.xml", s_menu_id, &m_game_objects, &m_texture_ids);
	m_callbacks.push_back(0);
	m_callbacks.push_back(s_menu_to_play);
	m_callbacks.push_back(s_exit_from_menu);

	set_callbacks(m_callbacks);

	std::cout << "Entering MenuState\n";
	return true;
}


bool MainMenuState::on_exit()
{

	// m_exiting = true;
	for(auto& go : m_game_objects) 
	{
		go->clean();
	}
	m_game_objects.clear();
	//bullshit right ?
	TextureMgr::get_instance()->clear_from_texture_map("playbutton");
	TextureMgr::get_instance()->clear_from_texture_map("exitbutton");

	std::cout << "Exiting MenuState\n";
	return true;
}

void MainMenuState::s_menu_to_play()
{
	std::cout << "Play button clicked !" << std::endl;
	Game::get_instance()->get_state_machine()->change_state(new PlayState());
}

void MainMenuState::s_exit_from_menu()
{
	std::cout << "Exit button clicked ! Goodbye :D" << std::endl;
	Game::get_instance()->quit();

}

void MainMenuState::set_callbacks(const std::vector<Callback>& cbcks)
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