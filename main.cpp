#include "Game.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS; //time we want a frame to take 

Game *g_game = nullptr; 

int main(int argc, char const *argv[])
{
	Uint32 frame_start, frame_time;
	g_game = Game::get_instance();

	if (Game::get_instance()->init("Now a singleton", 100, 100, 640, 480, 0)){
		while(Game::get_instance()->running())
		{
			frame_start = SDL_GetTicks();

			Game::get_instance()->handle_events();
			Game::get_instance()->update();
			Game::get_instance()->render();

			frame_time = SDL_GetTicks() - frame_start;

			if (frame_time < DELAY_TIME)
				SDL_Delay(DELAY_TIME - frame_time);
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