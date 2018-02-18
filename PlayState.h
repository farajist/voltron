#ifndef __PLAY_STATE__
#define __PLAY_STATE__

#include <iostream>
#include <string>
#include "GameState.h"

class PlayState : public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool on_enter();
	virtual bool on_exit();

	virtual std::string state_id() const { return s_play_id; };

private:
	static const std::string s_play_id;
};
#endif /* __PLAY_STATE__ */