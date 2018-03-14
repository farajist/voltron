#ifndef __MAIN_MENU_STATE__
#define __MAIN_MENU_STATE__

#include <iostream>
#include <string>
#include <vector>

#include "TextureManager.h"
#include "MenuState.h"
#include "GameObject.h"
#include "MenuButton.h"

#include "StateParser.h"

class MainMenuState : public MenuState
{
public:
	typedef TextureManager TextureMgr;
	virtual void update();
	virtual void render();

	virtual bool on_enter();
	virtual bool on_exit();

	virtual std::string state_id() const { return s_menu_id; };

private:

	static void s_menu_to_play();
	static void s_exit_from_menu();

	virtual void set_callbacks(const std::vector<Callback>&);
	static const std::string s_menu_id;
	std::vector<GameObject*> m_game_objects;
};

#include "Game.h"
#endif /* __MAIN_MENU_STATE__ */