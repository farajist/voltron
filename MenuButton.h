#ifndef __MENU_BUTTON_H__
#define __MENU_BUTTON_H__

#include "ShooterObject.h"
#include "GameObjectFactory.h"

class MenuButton : public ShooterObject
{
public:
	MenuButton();

	virtual void draw();
	virtual void update();
	virtual void clean();

	void load(std::unique_ptr<LoaderParams> const &p_params);
	
	void set_callback(void(*callback)()) { m_callback = callback; }
	int get_callback_id() { return m_callback_id; }

private:
	void (*m_callback) ();
	int m_callback_id;
	bool m_breleased;

	enum button_state
	{
		MOUSE_OUT = 0,
		MOUSE_OVER = 1,
		CLICKED = 2
	};
};

class MenuButtonCreator : public BaseCreator
{
	GameObject* create_game_object() const 
	{
		return new MenuButton();
	}
};

#endif /* __MENU_BUTTON_H__*/