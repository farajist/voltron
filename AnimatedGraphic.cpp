#include "AnimatedGraphic.h"

AnimatedGraphic::AnimatedGraphic() : SDLGameObject()
{

}

void AnimatedGraphic::load(const LoaderParams* p_params)
{
	SDLGameObject::load(p_params);
	m_anim_speed = p_params->get_anim_speed();
}

void AnimatedGraphic::draw() 
{
	SDLGameObject::draw();
}
void AnimatedGraphic::update() 
{
	//yeah this too -_* !
	m_curr_frame = int(((SDL_GetTicks() / (1000 / m_anim_speed)) % m_frames_count));
	// SDLGameObject::update();
}
void AnimatedGraphic::clean()
{
	SDLGameObject::clean();
}