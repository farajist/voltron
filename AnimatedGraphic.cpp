#include "AnimatedGraphic.h"

AnimatedGraphic::AnimatedGraphic() : ShooterObject()
{

}

void AnimatedGraphic::load(std::unique_ptr<LoaderParams> const &p_params)
{
	ShooterObject::load(p_params);
	m_anim_speed = p_params->get_anim_speed();
}

void AnimatedGraphic::draw() 
{
	ShooterObject::draw();
}
void AnimatedGraphic::update() 
{
	//yeah this too -_* !
	m_curr_frame = int(((SDL_GetTicks() / (1000 / m_anim_speed)) % m_num_frames));
	// ShooterObject::update();
}
void AnimatedGraphic::clean()
{
	ShooterObject::clean();
}