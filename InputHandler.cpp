#include "InputHandler.h"

InputHandler *InputHandler::sp_instance = 0;
InputHandler::InputHandler() : m_mouse_pos(new Vector2D(0, 0))
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

    if (SDL_NumJoysticks() > 0)
    {
        for (int i = 0; i < SDL_NumJoysticks(); ++i)
        {
            /* if succeeded to open add it to our vector, else
            report error*/

            SDL_Joystick *joy = SDL_JoystickOpen(i);
            if (joy)
            {
                m_joysticks.push_back(joy);

                m_joy_vals.push_back(std::make_pair(new Vector2D(0, 0), new Vector2D(0, 0))); //add pair of vectors
                std::vector<bool> temp_btns;
                //push false for each button as it's not pressed
                for (int j = 0; j < SDL_JoystickNumButtons(joy); ++j)
                    temp_btns.push_back(false);
                //push states to each joystick ;)
                m_button_states.push_back(temp_btns);
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
    // mouse buttons initialization part
    for (int i = 0; i < 3; ++i)
        m_mouse_btn_states.push_back(false);
}
//TODO: this is getting serious , please make subroutines
void InputHandler::update()
{
    SDL_Event event;
    //okay this is evil
    m_keystates = const_cast<Uint8 *>(SDL_GetKeyboardState(0));
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            Game::get_instance()->quit();
            break;
        case SDL_JOYAXISMOTION:
            on_joystick_axis_move(event);
            break;
        case SDL_JOYBUTTONDOWN: //a joystick button was pressed
            on_joystick_button_down(event);
            break;
        case SDL_JOYBUTTONUP: //a joystick button was released
            on_joystick_button_up(event);
            break;
        //[why init the enum with our values why not just use predefined and directly map below ?]
        //a mouse was button pressed
        case SDL_MOUSEMOTION: //mouse is being moved around
            on_mouse_move(event);
            break;
        case SDL_MOUSEBUTTONDOWN:
            on_mouse_button_down(event);
            break;
        case SDL_MOUSEBUTTONUP:
            on_mouse_button_up(event);
            break;
        case SDL_KEYDOWN:
            on_key_down();
            break;
        case SDL_KEYUP:
            on_key_up();
            break;
        default:
            break;
        }
    }
}

//keyboard events
void InputHandler::on_key_down()
{
    m_keystates = const_cast<Uint8 *>(SDL_GetKeyboardState(0));
}

void InputHandler::on_key_up()
{
    m_keystates = const_cast<Uint8 *>(SDL_GetKeyboardState(0));
}

//mouse event
void InputHandler::on_mouse_move(SDL_Event &event)
{
    m_mouse_pos->set_x(event.motion.x);
    m_mouse_pos->set_y(event.motion.y);
}

void InputHandler::on_mouse_button_down(SDL_Event &event)
{
    if (event.button.button == SDL_BUTTON_LEFT)
        m_mouse_btn_states[LEFT] = true;
    if (event.button.button == SDL_BUTTON_MIDDLE)
        m_mouse_btn_states[MIDDLE] = true;
    if (event.button.button == SDL_BUTTON_RIGHT)
        m_mouse_btn_states[RIGHT] = true;
}

void InputHandler::on_mouse_button_up(SDL_Event &event)
{
    if (event.button.button == SDL_BUTTON_LEFT)
        m_mouse_btn_states[LEFT] = false;
    if (event.button.button == SDL_BUTTON_MIDDLE)
        m_mouse_btn_states[MIDDLE] = false;
    if (event.button.button == SDL_BUTTON_RIGHT)
        m_mouse_btn_states[RIGHT] = false;
}

//joystick events
void InputHandler::on_joystick_axis_move(SDL_Event &event)
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

void InputHandler::on_joystick_button_down(SDL_Event &event)
{
    int which_one = event.jaxis.which;
    m_button_states[which_one][event.jbutton.button] = true;
}

void InputHandler::on_joystick_button_up(SDL_Event &event)
{
    int which_one = event.jaxis.which;
    m_button_states[which_one][event.jbutton.button] = false;
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

bool InputHandler::get_button_state(int joy, int btn_nb)
{
    return m_button_states[joy][btn_nb];
}

bool InputHandler::get_mouse_btn_state(int btn_nb)
{
    return m_mouse_btn_states[btn_nb];
}
Vector2D *InputHandler::get_mouse_pos()
{
    return m_mouse_pos;
}

bool InputHandler::is_key_down(SDL_Scancode key)
{
    if (m_keystates != 0)
    {
        return (m_keystates[key] == 1);
    }
    return false;
}

InputHandler::~InputHandler()
{
    if (m_mouse_pos)
        delete m_mouse_pos;
    if (m_keystates)
        delete m_keystates;
}