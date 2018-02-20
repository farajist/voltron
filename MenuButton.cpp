#include "MenuButton.h"

MenuButton::MenuButton(const LoaderParams* p_params) :
SDLGameObject(p_params)
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
		m_curr_frame = MOUSE_OVER;
		if (InputHandler::get_instance()->get_mouse_btn_state(LEFT))
		{
			m_curr_frame = CLICKED;
		}
	}
	else
	{
		m_curr_frame = MOUSE_OUT;
	}
}

void MenuButton::clean()
{
	SDLGameObject::clean();
}