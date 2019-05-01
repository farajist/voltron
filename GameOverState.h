#ifndef __GAME_OVER_STATE__
#define __GAME_OVER_STATE__

#include <iostream>
#include <string>
#include <vector>

// #include "TextureManager.h"
#include "MenuState.h"
// #include "GameObject.h"
// #include "MenuButton.h"
// #include "AnimatedGraphic.h"


class GameOverState : public MenuState 
{
public:
	typedef TextureManager TextureMgr;
	virtual void update();
	virtual void render();

	virtual bool on_enter();
	virtual bool on_exit();

	virtual std::string state_id() const { return s_game_over_id; };

private:

	virtual void set_callbacks(const std::vector<Callback>&);
	
	static void s_game_over_to_main();
	static void s_restart_play();

	static const std::string s_game_over_id;
	std::vector<GameObject*> m_game_objects;
};

#endif /* __GAME_OVER_STATE__ */