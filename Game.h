#ifndef __GAME__
#define __GAME__

#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// #include "TextureManager.h"
// #include "GameObject.h"
// #include "Player.h"
// #include "Enemy.h"
// #include "InputHandler.h"
#include "GameStateMachine.h"
// #include "PlayState.h"
// #include "MainMenuState.h"


class Game
{
public:

	bool init(std::string title, int xpos, int ypos, int width, int height,
			int flags);
	void render();
	void update();
	void handle_events();
	void clean();
	void quit();
	bool running() {return mb_running;}

	static Game* get_instance();
	SDL_Renderer* get_renderer() const { return mp_renderer; }
	GameStateMachine* get_state_machine() {return m_pgame_state_machine; }

	int get_width() const {return m_game_width;}
	int get_height() const {return m_game_height;} 
	
	
	void set_current_level(int);
	const int get_current_level() { return m_current_level; }

	const bool get_level_complete() { return mb_level_complete; }
	void set_level_complete(bool is_complete) { mb_level_complete = is_complete; }

	void set_player_lives(int lives) { m_player_lives = lives; }
	int get_player_lives() { return m_player_lives; }

	void set_next_level(int next_level) { m_next_level = next_level; }
    const int get_next_level() { return m_next_level; }

private:
	//singleton matters
	
	static Game* sp_instance;

	SDL_Window* mp_window;
	SDL_Renderer* mp_renderer;

	GameStateMachine* m_pgame_state_machine;


	int m_current_frame;
	bool mb_running;
	int m_game_width;
	int m_game_height;

	int m_player_lives;
	int m_current_level;
	int m_next_level;
	bool mb_level_complete;
	bool mb_changing_state;
	std::vector<std::string> m_level_files;


	
	Game();
	~Game();
	Game(const Game&);
	Game& operator=(const Game&)	;
};
#endif /*__GAME__*/
