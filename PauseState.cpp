#include "PauseState.h"


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
	
	if (!TextureMgr::get_instance()->load("assets/resume.png", 
	"resumebutton", Game::get_instance()->get_renderer()))
	{
		return false;
	}
	if (!TextureMgr::get_instance()->load("assets/main.png",
	"mainbutton", Game::get_instance()->get_renderer()))
	{
		return false;
	}
	
	GameObject* btn_resume = new MenuButton(new LoaderParams(200, 100,
	200, 80, "resumebutton"), PauseState::s_resume_play);

	GameObject* btn_main = new MenuButton(new LoaderParams(200, 200,
	200, 80, "mainbutton"), PauseState::s_pause_to_main);

	m_game_objects.push_back(btn_resume);
	m_game_objects.push_back(btn_main);

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
	TextureMgr::get_instance()->clear_from_texture_map("resumebutton");
	TextureMgr::get_instance()->clear_from_texture_map("mainbutton");

	std::cout << "Exiting PauseState\n";
	return true;
}



void PauseState::s_pause_to_main()
{
	Game::get_instance()->get_state_machine()->change_state(new MenuState());
}

void PauseState::s_resume_play()
{
	Game::get_instance()->get_state_machine()->pop_state();
}