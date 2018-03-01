#include "PlayState.h"

const std::string PlayState::s_play_id = "PLAY";

void PlayState::update()
{
	if (InputHandler::get_instance()->is_key_down(SDL_SCANCODE_ESCAPE))
	{
		Game::get_instance()->get_state_machine()->push_state(new PauseState());
	}
	for (auto &go : m_game_objects)
	{
		go->update();
	}

	if (check_collision(dynamic_cast<SDLGameObject*>(m_game_objects[0]),
	dynamic_cast<SDLGameObject*>(m_game_objects[1])))
	{
		Game::get_instance()->get_state_machine()->push_state(new GameOverState());
	}
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

	if (!TextureMgr::get_instance()->load("assets/helicopter_en.png", "heli_en",
	Game::get_instance()->get_renderer()))
	{
		return false;
	}


	GameObject *player = new Player(new LoaderParams(500, 100, 128, 55, "heli"));
	// m_game_objects.push_back(player); => wirus
	
	GameObject *enemy = new Enemy(new LoaderParams(100, 100, 128, 55, "heli_en"));
	m_game_objects.push_back(player);
	m_game_objects.push_back(enemy);

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

bool PlayState::check_collision(SDLGameObject* a, SDLGameObject* b)
{
	int left_a, left_b;
	int right_a, right_b;
	int top_a, top_b;
	int bottom_a, bottom_b;


	left_a = a->get_pos().get_x();
	right_a = a->get_pos().get_x() + a->get_width();
	top_a = a->get_pos().get_y();
	bottom_a = a->get_pos().get_y() + a->get_height();

	//sides of object b,
	left_b = b->get_pos().get_x();
	right_b = b->get_pos().get_x() + b->get_width();
	top_b = b->get_pos().get_y();
	bottom_b = b->get_pos().get_y() + b->get_height();

	// std::cout << left_a << " " << right_a << " " << top_a << " " << bottom_a << std::endl; 
	// std::cout << left_b << " " << right_b << " " << top_b << " " << bottom_b << std::endl;

	//bear withit now, init for rights and bottoms should be shortcut ! :3
	// projection collision detection see lazy foo
	if (bottom_a <= top_b) return false;
	if (top_a >= bottom_b) return false;
	if (right_a <= left_b) return false;
	if (left_a >= right_b) return false;
	
	return true;	
}