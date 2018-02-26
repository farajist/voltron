#include "GameStateMachine.h"


void GameStateMachine::push_state(GameState* p_state)
{
	m_game_states.push_back(p_state);
	m_game_states.back()->on_enter();
}

void GameStateMachine::change_state(GameState* p_state)
{
	if (!m_game_states.empty())
	{
		if (m_game_states.back()->state_id() == p_state->state_id())
			return;
			//private leave to avoid repitition !
		if (m_game_states.back()->on_exit()) 
		{
			// delete m_game_states.back(); => headache wallah
			m_game_states.pop_back();
		}
	}
	m_game_states.push_back(p_state);
	m_game_states.back()->on_enter();
}

void GameStateMachine::pop_state()
{
	if (!m_game_states.empty())
	{
		if (m_game_states.back()->on_exit())
		{
			delete m_game_states.back();
			m_game_states.pop_back();
		}
	}
}

void GameStateMachine::update() 
{
	if (!m_game_states.empty())
	{
		m_game_states.back()->update();
	}
}

void GameStateMachine::render() 
{
	if (!m_game_states.empty())
	{
		m_game_states.back()->render();
	}
}