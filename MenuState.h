#ifndef __MENU_STATE__
#define __MENU_STATE__

#include <vector>
#include "GameState.h"

/**
 * This class is a super class for all state types
 * with callbacks !
 * */
class MenuState : public GameState
{
protected:
	typedef void(*Callback)();

	virtual void set_callbacks(const std::vector<Callback>&) = 0;
	
	std::vector<Callback> m_callbacks;
};


#endif /* __MAIN_MENU_STATE__ */