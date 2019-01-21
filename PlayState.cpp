#include "PlayState.h"

const std::string PlayState::s_play_id = "PLAY";

void PlayState::update()
{
	// if (InputHandler::get_instance()->is_key_down(SDL_SCANCODE_ESCAPE))
	// {
	// 	Game::get_instance()->get_state_machine()->push_state(new PauseState());
	// }
	// for (auto &go : m_game_objects)
	// {
	// 	go->update();
	// }

	// if (check_collision(dynamic_cast<SDLGameObject*>(m_game_objects[0]),
	// dynamic_cast<SDLGameObject*>(m_game_objects[1])))
	// {
	// 	Game::get_instance()->get_state_machine()->push_state(new GameOverState());
	// }

	p_level->update();
}

void PlayState::render()
{
	// for (auto &go : m_game_objects)
		// go->draw();

		p_level->render();
}

bool PlayState::on_enter()
{
	// StateParser parser;
	// parser.parse_state("test.xml", s_play_id, &m_game_objects, &m_texture_ids);
	LevelParser parser;
	p_level = parser.parse_level("map_ex.tmx");

	std::cout << "Level parsed, we have " << p_level->get_layers()->size() << " layers now !" <<std::endl;
	std::cout << "Tileset gids are : " <<std::endl;
	for (auto& ts : *(p_level->get_tilesets()))
		std::cout << ts.first_gid << " ";
	std::cout << std::endl;
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
	for (auto& ti : m_texture_ids)
		TextureMgr::get_instance()->clear_from_texture_map(ti);

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