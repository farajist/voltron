#ifndef __SDL_GAME_OBJECT__
#define __SDL_GAME_OBJECT__

#include "GameObject.h"
#include "Vector2D.h"


class SDLGameObject : public GameObject
{
public:
	SDLGameObject(const LoaderParams* p_params);
	virtual void update();
	virtual void draw();
	virtual void clean();
protected:

	Vector2D m_pos;

	int m_width;
	int m_height;

	int m_curr_row;
	int m_curr_frame;

	std::string m_texture_id;
	
};

#include "Game.h"
#endif /* __SDL_GAME_OBJECT__ */