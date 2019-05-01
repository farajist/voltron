#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include <iostream>
#include <string>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Vector2D.h"
#include "TextureManager.h"
#include "LoaderParams.h"

class GameObject
{
public:
	typedef TextureManager TextureMgr;	

	//draw the object
	virtual void draw() = 0; 
	
	//do update stuff (physics and vectors)
	virtual void update() = 0;
	
	//clean all need-to-be-deleted stuff
	virtual void clean() = 0;


	//object has collided : handle accordingly 
	virtual void collision() = 0;

	// get the type of the object
	virtual std::string type() = 0;

	//new load from file
	virtual void load(std::unique_ptr<LoaderParams> const &p_params) = 0;
	//base class needs virtual destructor
	virtual ~GameObject() {}


	//getters for common fields
	Vector2D& get_position() { return m_pos; }
	Vector2D& get_vel() { return m_vel; }
	int get_width() { return m_width; }
	int get_height() { return m_height; }

	//scroll along the tile map
	void scroll(float scroll_speed) {
		m_pos.set_x(m_pos.get_x() - scroll_speed);
	}

	//is the object being updated ?
	bool updating() { return mb_updating; }

	//is the object dead ?
	bool dead() { return mb_dead; }

	//is the object dying ? (for animation)
	bool dying() { return mb_dying; }
	// whether to update the object or not
	void set_updating(bool updating) {
		mb_updating = updating;
	}

protected:
	//constructor with default initialisation list
	GameObject():  
	m_pos(0,0),
	m_vel(0,0),
	m_accel(0,0),
	m_width(0),
	m_height(0),
	m_curr_row(0),
	m_curr_frame(0),
	mb_updating(false),
	mb_dead(false),
	mb_dying(false),
	m_angle(0),
	m_alpha(0xFF)
	{

	}
	
	//movement fields
	Vector2D m_pos;
	Vector2D m_vel;
	Vector2D m_accel;

	//size fields
	int m_width;
	int m_height;

	//animation fields
	int m_curr_row;
	int m_curr_frame;
	int m_num_frames;
	std::string m_texture_id;

	//common bool fields 
	bool mb_updating;
	bool mb_dead;
	bool mb_dying;

	//rotation
	double m_angle;

	//blending
	int m_alpha;
};


#endif /*__GAME_OBJECT__*/