#include "AnimatedGraphic.h"

AnimatedGraphic::AnimatedGraphic(const LoaderParams *p_params, int anim_speed) 
: SDLGameObject(p_params), m_anim_speed(anim_speed)
{

}
void AnimatedGraphic::draw() 
{
	SDLGameObject::draw();
}
void AnimatedGraphic::update() 
{
	//yeah this too -_* !
	m_curr_frame = int((SDL_GetTicks() / (1000 / m_anim_speed) % 2));
	SDLGameObject::update();
}
void AnimatedGraphic::clean()
{
	SDLGameObject::clean();
}