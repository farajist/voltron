#ifndef __PLAYER__
#define __PLAYER__

#include "ShooterObject.h"
#include "LoaderParams.h"

//This may be in ShooterObject :v
#include "InputHandler.h"
#include "BulletHandler.h"
#include "SoundManager.h"
#include "GameObjectFactory.h"

class Player : public ShooterObject
{
public:
	Player();
	virtual ~Player() {}

	virtual void load(std::unique_ptr<LoaderParams> const &p_params);
    
    virtual void draw();
    virtual void update();
    virtual void clean();
    
    virtual void collision();
    
    virtual std::string type() { return "Player"; }

private:

	//bring back to life if live left
	void resurrect();
	void handle_input();

	void handle_animation();

	// player can be invulnerable for a time
	int m_invulnerable;
	int m_invulnerable_time;
	int m_invulnerable_counter;
};

class PlayerCreator : public BaseCreator
{
	GameObject* create_game_object() const 
	{
		return new Player();
	}
};

#endif /*__PLAYER__*/