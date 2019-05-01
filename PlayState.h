#ifndef __PLAY_STATE__
#define __PLAY_STATE__

#include <iostream>
#include <string>
#include <vector>

#include "GameState.h"
#include "Level.h"
#include "CollisionManager.h"


class GameObject;
class Level;

class PlayState : public GameState
{
public:
	typedef TextureManager TextureMgr;

	virtual void update();
	virtual void render();

	virtual bool on_enter();
	virtual bool on_exit();

	virtual std::string state_id() const { return s_play_id; };

private:
	static const std::string s_play_id;
	bool check_collision(ShooterObject*, ShooterObject*);
	std::vector<GameObject*> m_game_objects;

	Level* p_level;
};

#include "Game.h"
#endif /* __PLAY_STATE__ */