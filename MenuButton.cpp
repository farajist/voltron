#include "MenuButton.h"

MenuButton::MenuButton(const LoaderParams* p_params, void (*callback)()) :
SDLGameObject(p_params), m_callback(callback)
{
	m_curr_frame = MOUSE_OUT;
}

void MenuButton::draw()
{
	SDLGameObject::draw();
}

void MenuButton::update()
{
	Vector2D* p_mouse_pos = InputHandler::get_instance()
							->get_mouse_pos();

	//simply put : if the cursor is confined within the 
	//frame of the button : functionalify !!
	if (p_mouse_pos->get_x() < (m_pos.get_x() + m_width)
	&& p_mouse_pos->get_x() > m_pos.get_x()
	&& p_mouse_pos->get_y() < (m_pos.get_y() + m_height)
	&& p_mouse_pos->get_y() > m_pos.get_y())
	{
		// m_curr_frame = MOUSE_OVER;
		if (InputHandler::get_instance()->get_mouse_btn_state(LEFT) && m_breleased)
		{
			m_curr_frame = CLICKED;

			m_callback(); //call to callback func
			m_breleased = false;
		}
		else if (!InputHandler::get_instance()->get_mouse_btn_state(LEFT))
		{
			m_breleased = true;
			m_curr_frame = MOUSE_OVER;
		}
	}
	else
	{
		m_curr_frame = MOUSE_OUT;
	}
	//returns call to a dead object when state is changed !!!
}

void MenuButton::clean()
{
	SDLGameObject::clean();
}

void MenuButton::s_menu_to_play()
{
	std::cout << "Play button clicked !" << std::endl;
	Game::get_instance()->get_state_machine()->change_state(new PlayState());
}

void MenuButton::s_exit_from_menu()
{
	std::cout << "Exit button clicked ! Goodbye :D" << std::endl;
	Game::get_instance()->quit();

}