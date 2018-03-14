#include "Enemy.h"

Enemy::Enemy() : SDLGameObject() 
{
	
}

void Enemy::load(const LoaderParams* p_params)
{
	SDLGameObject::load(p_params);
	m_vel.set_y(2);
	m_vel.set_x(0.001);
}

void Enemy::draw() 
{
	// std::cout << "Enemy's draw function called !" << std::endl;
	SDLGameObject::draw();
}
void Enemy::update() 
{
	// std::cout << "Enemy's update function called !" << std::endl;
	// m_pos.set_x(m_pos.get_x() + 1);
	// m_y += 1;

	//hardcode for now -_x !
	m_curr_frame = int(((SDL_GetTicks() / 100) % 5));
	// std::cout << "current frame " << m_curr_frame << std::endl;

	if (m_pos.get_y() < 0)
		m_vel.set_y(2);
	else if (m_pos.get_y() > 480)
		m_vel.set_y(-2);

	SDLGameObject::update();
}
void Enemy::clean()
{
	SDLGameObject::clean();
	// std::cout << "Enemy's clean function called !" << std::endl;
}