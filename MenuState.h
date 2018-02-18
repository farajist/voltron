#ifndef __MENU_STATE__
#define __MENU_STATE__

#include <iostream>
#include <string>
#include "GameState.h"

class MenuState : public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool on_enter();
	virtual bool on_exit();

	virtual std::string state_id() const { return s_menu_id; };

private:
	static const std::string s_menu_id;
};
#endif /* __MENU_STATE__ */