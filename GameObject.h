#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "TextureManager.h"
#include "LoaderParams.h"

class GameObject
{
public:
	typedef TextureManager TextureMgr;	

	// virtual void load(int, int, int, int, std::string);
	virtual void draw(); //gotta remove the renderer ! => done
	virtual void update();
	virtual void clean();

	//new load function to avoid passing param to creator
	virtual void load(const LoaderParams*) = 0;


protected:
	GameObject() {}
	virtual ~GameObject() {}
};


#endif /*__GAME_OBJECT__*/