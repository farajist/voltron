#ifndef __GAME_STATE__
#define __GAME_STATE__

#include <vector>
#include <string>

class GameState 
{	
public:
	virtual void update() = 0;
	virtual void render() = 0;

	virtual bool on_enter() = 0;
	virtual bool on_exit() = 0;

	virtual std::string state_id() const = 0;

	virtual ~GameState(){}

protected:
	std::vector<std::string> m_texture_ids;

// protected:
// 	bool m_exiting;
};

#endif /* __GAME_STATE__ */