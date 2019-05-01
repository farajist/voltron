#include "MenuButton.h"
#include "InputHandler.h"
MenuButton::MenuButton() : ShooterObject()
{
	// m_curr_frame = MOUSE_OUT;
}

void MenuButton::load(std::unique_ptr<LoaderParams> const &p_params) 
{
	ShooterObject::load(p_params);
	m_callback_id = p_params->get_callback_id();
	m_curr_frame = MOUSE_OUT;
}
void MenuButton::draw()
{
	ShooterObject::draw();
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
			std::cout << "here we go" << std::endl;
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
	ShooterObject::clean();
}
