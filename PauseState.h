#ifndef __PAUSE_STATE__
#define __PAUSE_STATE__
#include <iostream>
#include <string>
#include <vector>

#include "TextureManager.h"
#include "GameState.h"
#include "GameObject.h"
#include "MenuButton.h"


class PauseState : public GameState 
{
public:
	typedef TextureManager TextureMgr;
	virtual void update();
	virtual void render();

	virtual bool on_enter();
	virtual bool on_exit();

	virtual std::string state_id() const { return s_pause_id; };

private:

	static void s_pause_to_main();
	static void s_resume_play();

	static const std::string s_pause_id;
	std::vector<GameObject*> m_game_objects;
};

#endif /* __PAUSE_STATE__ */