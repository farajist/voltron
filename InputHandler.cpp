#include "InputHandler.h"

InputHandler* InputHandler::sp_instance = 0;
InputHandler::InputHandler() 
{

}

void InputHandler::init_joysticks() 
{
    /* check whether the joystick subsystem has been initialized
    if not then initialize it */
    if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    /* now let's open each one (joystick), we do that by looping through 
    number of connected joys, if none set state of init to false*/

    if(SDL_NumJoysticks() > 0)
    {
        for (int i = 0; i < SDL_NumJoysticks(); ++i)
        {
            /* if succeeded to open add it to our vector, else
            report error*/

            SDL_Joystick *joy = SDL_JoystickOpen(i);
            if (joy)
            {
                m_joysticks.push_back(joy);

                m_joy_vals.push_back(std::make_pair(new 
                Vector2D(0,0), new Vector2D(0,0))); //add pair of vectors
            }
            else
                std::cout << "Couldn't open joystick n " << i << SDL_GetError() << std::endl;

        }
        //tell SDL that we're listening for joystick events
        SDL_JoystickEventState(SDL_ENABLE);
        //set the state of init to true
        mb_joysticks_inited = true;

        std::cout << "Initialized " << m_joysticks.size() << " joystick(s)" << std::endl;
    }
    else
    {
        mb_joysticks_inited = false;
        std::cout << "Initialized 0 joystick(s)" << std::endl;
    }
        
}

void InputHandler::update() 
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            Game::get_instance()->quit();
        if (event.type == SDL_JOYAXISMOTION) 
        {
            int which_one = event.jaxis.which;
            //left stick (right or left)
            if (event.jaxis.axis == 0) 
            {
                //right move
                if (event.jaxis.value > m_joy_dead_zone)
                    m_joy_vals[which_one].first->set_x(1);
                //left move
                else if (event.jaxis.value < -m_joy_dead_zone)
                    m_joy_vals[which_one].first->set_x(-1);
                else
                    m_joy_vals[which_one].first->set_x(0);
            }
            //left stick (up or down)
            if (event.jaxis.axis == 1) 
            {
                //up move
                if (event.jaxis.value > m_joy_dead_zone)
                    m_joy_vals[which_one].first->set_y(1);
                //down move
                else if (event.jaxis.value < -m_joy_dead_zone)
                    m_joy_vals[which_one].first->set_y(-1);
                else
                    m_joy_vals[which_one].first->set_y(0);
            }

            //right stick (right or left)
            if (event.jaxis.axis == 3) 
            {
                //right move
                if (event.jaxis.value > m_joy_dead_zone)
                    m_joy_vals[which_one].second->set_x(1);
                //left move
                else if (event.jaxis.value < -m_joy_dead_zone)
                    m_joy_vals[which_one].second->set_x(-1);
                else
                    m_joy_vals[which_one].second->set_x(0);
            }

            //right stick (up or down)
            if (event.jaxis.axis == 4) 
            {
                //up move
                if (event.jaxis.value > m_joy_dead_zone)
                    m_joy_vals[which_one].second->set_y(1);
                //down move
                else if (event.jaxis.value < -m_joy_dead_zone)
                    m_joy_vals[which_one].second->set_y(-1);
                else
                    m_joy_vals[which_one].second->set_y(0);
            }
        }
    }
}

/* clean loops through all our opened joys and closes them 
one by one !*/
void InputHandler::clean() 
{
    if (mb_joysticks_inited) 
    {
        for (decltype(SDL_NumJoysticks()) i = 0; i < SDL_NumJoysticks(); ++i)
            SDL_JoystickClose(m_joysticks[i]);
    }
}

int InputHandler::x_val(int joy, int stick) 
{
    if (m_joysticks.size() > 0) 
    {
        if (m_joy_vals.size() > 0)
        {
            if (stick == 1)
                return m_joy_vals[joy].first->get_x();
            else if (stick == 2)
                return m_joy_vals[joy].second->get_x();
        }
    }
    return 0;
}

int InputHandler::y_val(int joy, int stick)
{
    if (m_joysticks.size() > 0) 
    {
        if (m_joy_vals.size() > 0)
        {
            if (stick == 1)
                return m_joy_vals[joy].first->get_y();
            else if (stick == 2)
                return m_joy_vals[joy].second->get_y();
        }
    }
    return 0;
}