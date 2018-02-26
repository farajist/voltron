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
#include "MenuState.h"


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
private:
	//singleton matters
	Game() : mp_window(NULL), mp_renderer(NULL), mb_running(false){}
	static Game* sp_instance;

	SDL_Window* mp_window;
	SDL_Renderer* mp_renderer;

	// GameObject m_go;
	// Player m_player;

	GameStateMachine* m_pgame_state_machine;
	// std::vector<GameObject*> m_game_objects;

	// GameObject* m_player;
	// GameObject* m_go;
	// GameObject* m_en;


	int m_current_frame;
	bool mb_running;
};
#endif /*__GAME__*/
