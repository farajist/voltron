#ifndef __PLAY_STATE__
#define __PLAY_STATE__

#include <iostream>
#include <string>
#include <vector>

#include "GameState.h"
#include "GameObject.h"
#include "PauseState.h"
#include "TextureManager.h"

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
	std::vector<GameObject*> m_game_objects;
};

#include "Game.h"
#endif /* __PLAY_STATE__ */