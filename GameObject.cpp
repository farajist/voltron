#include "GameObject.h"
#include "TextureManager.h"

// void GameObject::load(int x, int y, int w, int h, std::string id)
// {
// 	m_x = x;
// 	m_y = y;
// 	m_width = w;
// 	m_height = h;
// 	m_texture_id = id;

// 	m_curr_row = 1;
// 	m_curr_frame = 1;
// }
void GameObject::draw()
{
	std::cout << "GameObject's draw function called !" << std::endl;
	// TextureMgr::get_instance()->draw_frame(m_texture_id, m_x, m_y,
	// 	m_width, m_height, m_curr_row, m_curr_frame, p_renderer);
}
void GameObject::update() 
{
	std::cout << "GameObject's update function called !" << std::endl;
	// m_x += 1;
	// m_curr_frame = int((SDL_GetTicks() / 100) % 10);
	// m_curr_row = (m_curr_frame + 1) % 1;
	// std::cout << "Current frame : " << m_curr_frame << std::endl;
}
void GameObject::clean()
{
	std::cout << "GameObject's clean function called !" << std::endl;
}