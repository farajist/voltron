#ifndef __ANIMATED_GRAPHIC__
#define __ANIMATED_GRAPHIC__

#include "SDLGameObject.h"
#include "LoaderParams.h"

class AnimatedGraphic : public SDLGameObject
{
public:

	AnimatedGraphic();
	void draw();
	void update();
	void clean();

	virtual void load(const LoaderParams*);

private:
	int m_anim_speed;
};


class AnimatedGraphicCreator : public BaseCreator
{
	GameObject* create_game_object() const 
	{
		return new AnimatedGraphic();
	}
};

#endif /* __ANIMATED_GRAPHIC__ */