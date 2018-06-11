#ifndef __GAME__
#define __GAME__

#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "InputHandler.h"
#include "GameStateMachine.h"
#include "PlayState.h"
#include "MainMenuState.h"


class Game
{
public:
	typedef TextureManager TextureMgr;
	// typedef Game TheGame;
	~Game();

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
private:
	//singleton matters
	Game() : mp_window(NULL), mp_renderer(NULL), mb_running(false){}
	static Game* sp_instance;

	SDL_Window* mp_window;
	SDL_Renderer* mp_renderer;

	GameStateMachine* m_pgame_state_machine;


	int m_current_frame;
	bool mb_running;
	int m_game_width;
	int m_game_height;
};
#endif /*__GAME__*/
