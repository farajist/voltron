#ifndef __MENU_STATE__
#define __MENU_STATE__

#include <iostream>
#include <string>
#include <vector>

#include "TextureManager.h"
#include "GameState.h"
#include "GameObject.h"
#include "MenuButton.h"

class MenuState : public GameState
{
public:
	typedef TextureManager TextureMgr;
	virtual void update();
	virtual void render();

	virtual bool on_enter();
	virtual bool on_exit();

	virtual std::string state_id() const { return s_menu_id; };

private:
	static const std::string s_menu_id;
	std::vector<GameObject*> m_game_objects;
};

#include "Game.h"
#endif /* __MENU_STATE__ */