#include "Player.h"

// void Player::load(int x, int y, int w, int h, std::string id) 
// {
// 	GameObject::load(x, y, w, h, id);
// }

Player::Player(const LoaderParams *p_params) : SDLGameObject(p_params) 
{
}

void Player::draw() 
{
	// std::cout << "Player's draw function called !" << std::endl;
	SDLGameObject::draw();
}

void Player::update() 
{
	// std::cout << "Player's update function called !" << std::endl;
	// m_pos.set_x(m_pos.get_x() + 1);
	m_vel.set_x(0);
	m_vel.set_y(0);

	handle_input();
	m_curr_frame = int((SDL_GetTicks() / 100) % 6);
	// m_vel.set_x(1);
	
	SDLGameObject::update();
}

void Player::clean()
{
	SDLGameObject::clean();
	std::cout << "Player's clean function called !" << std::endl;
}

void Player::handle_input() 
{
	Vector2D* target = InputHandler::get_instance()
	->get_mouse_pos();

	m_vel = *target - m_pos;
	m_vel /= 50;
}