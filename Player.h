#ifndef __PLAYER__
#define __PLAYER__

#include "SDLGameObject.h"
#include "LoaderParams.h"

//This may be in SDLGameObject :v
#include "InputHandler.h"
#include "GameObjectFactory.h"

class Player : public SDLGameObject
{
public: 

	// void load(int, int, int, int, std::string);
	Player();
	void draw();
	void update();
	void clean();

	void load(const LoaderParams*);
private:
	void handle_input();
};

class PlayerCreator : public BaseCreator
{
	GameObject* create_game_object() const 
	{
		return new Player();
	}
};

#endif /*__PLAYER__*/