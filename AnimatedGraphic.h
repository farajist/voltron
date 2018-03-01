#ifndef __ANIMATED_GRAPHIC__
#define __ANIMATED_GRAPHIC__

#include "SDLGameObject.h"
#include "LoaderParams.h"

class AnimatedGraphic : public SDLGameObject
{
public:

	AnimatedGraphic(const LoaderParams*, int);
	void draw();
	void update();
	void clean();

private:
	int m_anim_speed;
};
#endif /* __ANIMATED_GRAPHIC__ */