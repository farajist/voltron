#include "PlayState.h"

const std::string PlayState::s_play_id = "PLAY";

void PlayState::update()
{

}

void PlayState::render()
{

}

bool PlayState::on_enter()
{
	std::cout << "Entering PlayState\n";
	return true;
}


bool PlayState::on_exit()
{
	std::cout << "Exiting PlayState\n";
	return true;
}
