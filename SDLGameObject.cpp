#include "SDLGameObject.h"


SDLGameObject::SDLGameObject(const LoaderParams* p_params) :
GameObject(p_params), m_pos(p_params->get_x(), p_params->get_y()),
m_vel(0, 0), m_acc(0, 0)
{
	m_width = p_params->get_width();
	m_height = p_params->get_height();

	m_texture_id = p_params->get_texture_id();

	m_curr_row = 1;
	m_curr_frame = 1;
}

void SDLGameObject::draw()
{
	std::cout << "SDLGameObject's draw function called !" << std::endl;
	TextureMgr::get_instance()->draw_frame(m_texture_id, 
		(int) m_pos.get_x(), (int) m_pos.get_y(),
		m_width, m_height, m_curr_row, m_curr_frame, Game::get_instance()->get_renderer());
}
void SDLGameObject::update() 
{
	std::cout << "SDLGameObject's update function called !" << std::endl;
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

