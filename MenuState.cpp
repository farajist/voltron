#include "MenuState.h"

const std::string MenuState::s_menu_id = "MENU";

void MenuState::update()
{

}


void MenuState::render()
{

}

bool MenuState::on_enter()
{
	std::cout << "Entering MenuState\n";
	return true;
}


bool MenuState::on_exit()
{
	std::cout << "Exiting MenuState\n";
	return true;
}