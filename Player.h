#ifndef __PLAYER__
#define __PLAYER__

#include "SDLGameObject.h"
#include "LoaderParams.h"

//This may be in SDLGameObject :v
#include "InputHandler.h"

class Player : public SDLGameObject
{
public: 

	// void load(int, int, int, int, std::string);
	Player(const LoaderParams *p_params);
	void draw();
	void update();
	void clean();
private:
	void handle_input();
};
#endif /*__PLAYER__*/