#include "Enemy.h"

// void Enemy::load(int x, int y, int w, int h, std::string id) 
// {
// 	GameObject::load(x, y, w, h, id);
// }
Enemy::Enemy(const LoaderParams *p_params) : SDLGameObject(p_params) 
{

}
void Enemy::draw() 
{
	std::cout << "Enemy's draw function called !" << std::endl;
	SDLGameObject::draw();
}
void Enemy::update() 
{
	std::cout << "Enemy's update function called !" << std::endl;
	m_pos.set_x(m_pos.get_x() + 1);
	// m_y += 1;

	m_curr_frame = int(((SDL_GetTicks() / 100) % 10));
	std::cout << "current frame " << m_curr_frame << std::endl;
}
void Enemy::clean()
{
	SDLGameObject::clean();
	std::cout << "Enemy's clean function called !" << std::endl;
}