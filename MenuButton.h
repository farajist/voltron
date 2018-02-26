#ifndef __MENU_BUTTON_H__
#define __MENU_BUTTON_H__

#include "SDLGameObject.h"

class MenuButton : public SDLGameObject
{
public:
	MenuButton(const LoaderParams*, void (*callback)());

	virtual void draw();
	virtual void update();
	virtual void clean();

	static void s_menu_to_play();
	static void s_exit_from_menu();

private:
	void (*m_callback) ();
	bool m_breleased;

	enum button_state
	{
		MOUSE_OUT = 0,
		MOUSE_OVER = 1,
		CLICKED = 2
	};
};

#endif /* __MENU_BUTTON_H__*/