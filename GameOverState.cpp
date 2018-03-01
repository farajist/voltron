#include "GameOverState.h"

const std::string GameOverState::s_game_over_id = "GAME_OVER";

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
	
	if (!TextureMgr::get_instance()->load("assets/gameover.png", 
	"gameoverlabel", Game::get_instance()->get_renderer()))
	{
		return false;
	}

	if (!TextureMgr::get_instance()->load("assets/main.png",
	"mainbutton", Game::get_instance()->get_renderer()))
	{
		return false;
	}
	
	if (!TextureMgr::get_instance()->load("assets/restart.png",
	"restartbutton", Game::get_instance()->get_renderer()))
	{
		return false;
	}

	GameObject* game_over_label = new AnimatedGraphic(new LoaderParams(200, 100,
	190, 30, "gameoverlabel"), 2);

	GameObject* btn_main = new MenuButton(new LoaderParams(200, 200,
	200, 80, "mainbutton"), s_game_over_to_main);

	GameObject* btn_restart = new MenuButton(new LoaderParams(200, 300,
	200, 80, "restartbutton"), s_restart_play);

	m_game_objects.push_back(game_over_label);
	m_game_objects.push_back(btn_main);
	m_game_objects.push_back(btn_restart);

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
	TextureMgr::get_instance()->clear_from_texture_map("playbutton");
	TextureMgr::get_instance()->clear_from_texture_map("exitbutton");

	std::cout << "Exiting MenuState\n";
	return true;
}

void GameOverState::s_game_over_to_main()
{
	Game::get_instance()->get_state_machine()->change_state(new MenuState());
}

void GameOverState::s_restart_play()
{
	Game::get_instance()->get_state_machine()->change_state(new PlayState());
}