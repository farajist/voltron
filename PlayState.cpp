#include "PlayState.h"

const std::string PlayState::s_play_id = "PLAY";

void PlayState::update()
{
	// if (!m_exiting)
	// {
		for (auto &go : m_game_objects)
		{
			go->update();
		}
	// }
}

void PlayState::render()
{
	for (auto &go : m_game_objects)
		go->draw();
}

bool PlayState::on_enter()
{
	if (!TextureMgr::get_instance()->load("assets/helicopter.png", "heli",
	Game::get_instance()->get_renderer()))
	{
		return false;
	}
	GameObject *player = new Player(new LoaderParams(100, 100, 128, 55, "heli"));
	m_game_objects.push_back(player);
	
	std::cout << "Entering PlayState\n";
	return true;
}


bool PlayState::on_exit()
{
	// m_exiting = true;
	for(auto& go : m_game_objects) 
	{
		go->clean();
	}
	m_game_objects.clear();
	//bullshit right ?
	TextureMgr::get_instance()->clear_from_texture_map("heli");

	std::cout << "Exiting PlayState\n";
	return true;
}
