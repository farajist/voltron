#ifndef __PLAYER_BULLET_H__
#define __PLAYER_BULLET_H__

#include "ShooterObject.h"

class PlayerBullet: public ShooterObject
{
public:
    PlayerBullet(): ShooterObject()
    {

    }

    virtual ~PlayerBullet() {}
    virtual std::string type () { return "PlayerBullet"; }
    virtual void load(std::unique_ptr<LoaderParams> p_params, Vector2D heading)
    {
        ShooterObject::load(std::move(p_params));
        m_heading = heading;
    }

    virtual void draw() 
    {
        ShooterObject::draw();
    }

    virtual void collision()
    {
        mb_dead = true;
    }

    virtual void update()
    {
        m_vel.set_x(m_heading.get_x());
        m_vel.set_y(m_heading.get_y());

        ShooterObject::update();
    }

    virtual void clean()
    {
        ShooterObject::clean();
    }

private:
    Vector2D m_heading;
};
#endif /* __PLAYER_BULLET_H__ */