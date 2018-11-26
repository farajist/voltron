#ifndef __ENEMY__
#define __ENEMY__

#include "SDLGameObject.h"
#include "LoaderParams.h"

#include "GameObjectFactory.h"
class Enemy : public SDLGameObject
{
public:

	Enemy();
	void draw();
	void update();
	void clean();

	void load(const LoaderParams*);
};

class EnemyCreator : public BaseCreator
{
	GameObject* create_game_object() const 
	{
		return new Enemy();
	}
};

#endif /*__ENEMY__*/