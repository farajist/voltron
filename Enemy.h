#ifndef __ENEMY__
#define __ENEMY__

#include "SDLGameObject.h"
#include "LoaderParams.h"

class Enemy : public SDLGameObject
{
public:

	// void load(int, int, int, int, std::string);
	Enemy(const LoaderParams* p_params);
	void draw();
	void update();
	void clean();
};
#endif /*__ENEMY__*/