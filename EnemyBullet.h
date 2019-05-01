#ifndef __ENEMY_BULLET_H__
#define __ENEMY_BULLET_H__

#include "PlayerBullet.h"

class EnemyBullet: public PlayerBullet
{
public:
    EnemyBullet(): PlayerBullet()
    {

    }

    virtual ~EnemyBullet() {}
    virtual std::string type () { return "EnemyBullet"; }

};
#endif /* __ENEMY_BULLET_H__ */