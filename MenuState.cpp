#include "MenuState.h"

const std::string MenuState::s_menu_id = "MENU";

void MenuState::update()
{
	// if (!m_exiting)
	// {
		for (auto &go : m_game_objects)
		{
			go->update();
		}
	// }
}


void MenuState::render()
{
	//same as always : now in each game state a part
	for (auto &go : m_game_objects)
	{
		go->draw();
	}
}

bool MenuState::on_enter()
{
	
	if (!TextureMgr::get_instance()->load("assets/button.png", 
	"playbutton", Game::get_instance()->get_renderer()))
	{
		return false;
	}
	if (!TextureMgr::get_instance()->load("assets/exit.png",
	"exitbutton", Game::get_instance()->get_renderer()))
	{
		return false;
	}
	
	GameObject* btn_play = new MenuButton(new LoaderParams(100, 100,
	400, 100, "playbutton"), MenuState::s_menu_to_play);

	GameObject* btn_exit = new MenuButton(new LoaderParams(100, 300,
	400, 100, "exitbutton"), MenuState::s_exit_from_menu);

	m_game_objects.push_back(btn_play);
	m_game_objects.push_back(btn_exit);

	std::cout << "Entering MenuState\n";
	return true;
}


bool MenuState::on_exit()
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

void MenuState::s_menu_to_play()
{
	std::cout << "Play button clicked !" << std::endl;
	Game::get_instance()->get_state_machine()->change_state(new PlayState());
}

void MenuState::s_exit_from_menu()
{
	std::cout << "Exit button clicked ! Goodbye :D" << std::endl;
	Game::get_instance()->quit();

}