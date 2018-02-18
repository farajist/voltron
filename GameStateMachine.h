#ifndef __GAME_STATE_MACHINE__
#define __GAME_STATE_MACHINE__

#include <vector>
#include "GameState.h"

class GameStateMachine 
{
public:
	void push_state(GameState* p_state);
	void change_state(GameState* p_state);
	void pop_state();

	void update();
	void render();
	
private:
	std::vector<GameState*> m_game_states;
};

#endif /* __GAME_STATE_MACHINE__ */