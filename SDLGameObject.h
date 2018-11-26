#ifndef __SDL_GAME_OBJECT__
#define __SDL_GAME_OBJECT__

#include "GameObject.h"
#include "Vector2D.h"


class SDLGameObject : public GameObject
{
public:
	SDLGameObject();
	virtual void update();
	virtual void draw();
	virtual void clean();

	Vector2D& get_pos() { return m_pos; }
	int get_width() { return m_width; }
	int get_height() { return m_height; }
	
	virtual void load(const LoaderParams*);
protected:

	Vector2D m_pos;
	Vector2D m_vel;
	Vector2D m_acc;
	
	int m_width;
	int m_height;

	int m_curr_row;
	int m_curr_frame;
	int m_frames_count;

	std::string m_texture_id;
	
};

#include "Game.h"
#endif /* __SDL_GAME_OBJECT__ */