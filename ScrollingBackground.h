#ifndef __SCROLLING_BACKGROUND_H__
#define __SCROLLING_BACKGROUND_H__

#include <iostream>

#include "ShooterObject.h"
#include "GameObjectFactory.h"

class ScrollingBackground : public ShooterObject {

public:
    virtual ~ScrollingBackground() {}
    ScrollingBackground();

    virtual void draw();
    virtual void update();
    virtual void clean();

    virtual void load(std::unique_ptr<LoaderParams> const &params);

private:
    int m_scroll_speed;

    int count;
    int max_count;

    SDL_Rect m_src_rect1;
    SDL_Rect m_src_rect2;

    SDL_Rect m_dest_rect1;
    SDL_Rect m_dest_rect2;

    int m_src_rect1_w;
    int m_src_rect2_w;

    int m_dest_rect1_w;
    int m_dest_rect2_w;


};


class ScrollingBackgroundCreator : public BaseCreator
{
public:
    virtual GameObject* create_game_object() const 
    {
        return new ScrollingBackground();
    }
}; 
#endif /* __SCROLLING_BACKGROUND_H__ */