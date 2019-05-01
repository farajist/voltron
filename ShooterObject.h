#ifndef __SHOOTER_OBJECT__
#define __SHOOTER_OBJECT__

#include "GameObject.h"
#include "Vector2D.h"


class ShooterObject : public GameObject
{
public:
	virtual ~ShooterObject();
	virtual void update();
	virtual void draw();
	//not implemented
	virtual void clean();
	//collision : not implemented
	virtual void collision() {}

	virtual std::string type() { return "ShooterObject"; }


	// Vector2D& get_pos() { return m_pos; }
	// int get_width() { return m_width; }
	// int get_height() { return m_height; }
	
	virtual void load(std::unique_ptr<LoaderParams> const &p_params);
protected:

	// won't directly create ShooterObject
	ShooterObject();
	
	//draw the animation for object being destroyed
	void do_dying_animation();

	//how fast object emits bullets? counter
	int m_bullet_firing_speed;
	int m_bullet_counter;

	//how fast will it move
	int m_move_speed;

	// how long death animation takes ?
	int m_dying_time;
	int m_dying_counter;

	//has explosion sound played ?
	bool mb_played_death_sound;
	
};

#include "Game.h"
#endif /* __SHOOTER_OBJECT__ */