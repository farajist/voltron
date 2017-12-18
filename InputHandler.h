#ifndef __INPUT_HANDLER__
#define __INPUT_HANDLER__

#include <vector>
#include <SDL2/SDL.h>
#include "Vector2D.h"

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

    int x_val(int, int);
    int y_val(int, int);
    void update();
    void clean();
private:
    const int m_joy_dead_zone = 10000;
    std::vector<SDL_Joystick*> m_joysticks;
    std::vector<std::pair<Vector2D*, Vector2D*>> m_joy_vals;

    bool mb_joysticks_inited;

    InputHandler();
    ~InputHandler() {}
    static InputHandler* sp_instance;
};

#include "Game.h"
#endif /* __INPUT_HANDLER__ */