#include "Game.h"


Game *g_game = nullptr; 

int main(int argc, char const *argv[])
{
	g_game = Game::get_instance();

	if (Game::get_instance()->init("Now a singleton", 100, 100, 640, 480, 0)){
		while(Game::get_instance()->running())
		{
			Game::get_instance()->handle_events();
			Game::get_instance()->update();
			Game::get_instance()->render();

			// SDL_Delay(10);
		}	
	}
	else 
	{
		std::cout << "Game failed to init " << SDL_GetError() << std::endl;
		return -1;
	}
	std::cout << "Game overing xD !" << std::endl;
	Game::get_instance()->clean();
	return 0;
}