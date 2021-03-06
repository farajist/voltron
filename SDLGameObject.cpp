#include "SDLGameObject.h"

SDLGameObject::SDLGameObject() : GameObject()
{
	
}

void SDLGameObject::load(const LoaderParams* p_params)
{
	//vectors init
	m_pos = Vector2D(p_params->get_x(), p_params->get_y());
	m_vel = Vector2D(0, 0);
	m_acc = Vector2D(0, 0);

	m_width = p_params->get_width();
	m_height = p_params->get_height();
	m_texture_id = p_params->get_texture_id();
	m_curr_row = 1;
	m_curr_frame = 1;
	m_frames_count = p_params->get_num_frames();
}

void SDLGameObject::draw()
{
	// std::cout << "SDLGameObject's draw function called !" << std::endl;
	// TextureMgr::get_instance()->draw_frame(m_texture_id, 
	// 	(int) m_pos.get_x(), (int) m_pos.get_y(),
	// 	m_width, m_height, m_curr_row, m_curr_frame, Game::get_instance()->get_renderer());

	if (m_vel.get_x() > 0) 
	{
		TextureMgr::get_instance()->draw_frame(m_texture_id, (Uint32)m_pos.get_x(),
		(Uint32)m_pos.get_y(), m_width, m_height, m_curr_row, m_curr_frame,
		Game::get_instance()->get_renderer(), SDL_FLIP_HORIZONTAL);
	}
	else 
	{
		TextureMgr::get_instance()->draw_frame(m_texture_id, (Uint32)m_pos.get_x(),
		(Uint32)m_pos.get_y(), m_width, m_height, m_curr_row, m_curr_frame,
		Game::get_instance()->get_renderer());
	}
}
void SDLGameObject::update() 
{
	// std::cout << "SDLGameObject's update function called !" << std::endl;
	// m_x += 1;
	// m_curr_frame = int((SDL_GetTicks() / 100) % 10);
	// m_curr_row = (m_curr_frame + 1) % 1;
	// std::cout << "Current frame : " << m_curr_frame << std::endl;
	m_vel += m_acc;
	m_pos += m_vel;
}
void SDLGameObject::clean()
{
	std::cout << "GameObject's clean function called !" << std::endl;
}

