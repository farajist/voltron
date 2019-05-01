#ifndef __ENEMY__
#define __ENEMY__

#include "ShooterObject.h"
#include "LoaderParams.h"

#include "GameObjectFactory.h"
class Enemy : public ShooterObject
{
public:
	virtual std::string type() {
		return "Enemy";
	}
protected:
	int m_health;

	Enemy() : ShooterObject() {}
	virtual ~Enemy() {}
};

// class EnemyCreator : public BaseCreator
// {
// 	GameObject* create_game_object() const 
// 	{
// 		return new Enemy();
// 	}
// };

#endif /*__ENEMY__*/