#ifndef __INPUT_HANDLER__
#define __INPUT_HANDLER__

#include <vector>
#include <SDL2/SDL.h>
#include "Vector2D.h"
/**
 * helps with values of mouse buttons instead o
 * hardcode
*/
enum mouse_buttons
{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

class InputHandler {
public:

    static InputHandler* get_instance() 
    {
        if (sp_instance == 0) 
            sp_instance = new InputHandler();
        return sp_instance;
    }

    void init_joysticks();
    bool joysticks_initialised() {return mb_joysticks_inited;}

    bool get_button_state(int, int);
    bool get_mouse_btn_state(int);
    int x_val(int, int);
    int y_val(int, int);
    void update();
    void clean();
private:
    const int m_joy_dead_zone = 10000;
    std::vector<SDL_Joystick*> m_joysticks;
    std::vector<std::pair<Vector2D*, Vector2D*>> m_joy_vals;
    std::vector<std::vector<bool>> m_button_states;
    std::vector<bool> m_mouse_btn_states;
    bool mb_joysticks_inited;

    InputHandler();
    ~InputHandler() {}
    static InputHandler* sp_instance;
};

#include "Game.h"
#endif /* __INPUT_HANDLER__ */