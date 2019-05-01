#ifndef __COLLISION_H__
#define __COLLISION_H__
#include <SDL2/SDL.h>
#include "Vector2D.h"

const static int s_buffer = 4;
/**
 * buffer strategy is used to mitigate the "unfairness"
 * of exact rectangular collisions
 * */
static bool RectRect(SDL_Rect* a, SDL_Rect* b)
{
    int a_hbuf = a->h / s_buffer;
    int a_wbuf = a->w / s_buffer;

    int b_hbuf = b->h / s_buffer;
    int b_wbuf = b->w / s_buffer;

    //if bottom of A is less than top of b => no collision
    if ((a->y + a->h) - a_hbuf <= b->y + b_hbuf) return false;

    //if top of a is more that bottom of B => no collision
    if (a->y + a_hbuf >= (b->y + b->h) - b_hbuf) return false;

    //if the right of is less than the left of b => no collision
    if ((a->x + a->w) - a_wbuf <= b->x + b_wbuf) return false;

    //if the left of A is more than the right of b => n collision 
    if (a->x + a_wbuf >= (b->x + b->w) - b_wbuf) return false;

    // otherwise there has been a collision
    return true;
}

#endif /* __COLLISION_H__ */