#include "ShooterObject.h"

ShooterObject::ShooterObject() : GameObject(), m_bullet_firing_speed(0),
	m_bullet_counter(0),
	m_move_speed(0),
	m_dying_time(0),
	m_dying_counter(0),
	mb_played_death_sound(false)
{
	
}

void ShooterObject::load(std::unique_ptr<LoaderParams> const &p_params)
{
	//vectors init
	m_pos = Vector2D(p_params->get_x(), p_params->get_y());
	// m_vel = Vector2D(0, 0);
	// m_accel = Vector2D(0, 0);

	m_width = p_params->get_width();
	m_height = p_params->get_height();
	m_texture_id = p_params->get_texture_id();
	// m_curr_row = 1;
	// m_curr_frame = 1;
	m_num_frames = p_params->get_num_frames();
}

void ShooterObject::draw()
{
	// std::cout << "ShooterObject's draw function called !" << std::endl;
	// TextureMgr::get_instance()->draw_frame(m_texture_id, 
	// 	(int) m_pos.get_x(), (int) m_pos.get_y(),
	// 	m_width, m_height, m_curr_row, m_curr_frame, Game::get_instance()->get_renderer());

	// if (m_vel.get_x() > 0) 
	// {
	// 	TextureMgr::get_instance()->draw_frame(m_texture_id, (Uint32)m_pos.get_x(),
	// 	(Uint32)m_pos.get_y(), m_width, m_height, m_curr_row, m_curr_frame,
	// 	Game::get_instance()->get_renderer(), SDL_FLIP_HORIZONTAL);
	// }
	// else 
	// {
		TextureMgr::get_instance()->draw_frame(m_texture_id, (Uint32)m_pos.get_x(),
		(Uint32)m_pos.get_y(), m_width, m_height, m_curr_row, m_curr_frame,
		Game::get_instance()->get_renderer(), m_angle, m_alpha);
	// }
}
void ShooterObject::update() 
{
	// std::cout << "ShooterObject's update function called !" << std::endl;
	// m_x += 1;
	// m_curr_frame = int((SDL_GetTicks() / 100) % 10);
	// m_curr_row = (m_curr_frame + 1) % 1;
	// std::cout << "Current frame : " << m_curr_frame << std::endl;
	m_pos += m_vel;
	m_curr_frame = int(((SDL_GetTicks() / (1000 / 3)) % m_num_frames)) ;
	
}
void ShooterObject::clean()
{
	std::cout << "GameObject's clean function called !" << std::endl;
}

void ShooterObject::do_dying_animation()
{
	//keep scrolling with map 
	// scroll(Game::get_instance()->get_scroll_speed());

	m_curr_frame = int(((SDL_GetTicks() / (1000 / 3)) % m_num_frames));

	if (m_dying_counter == m_dying_time)
	{
		mb_dead = true;
	}
	m_dying_counter++; // simple counter, fine with fixed frame rate
}