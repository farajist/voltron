#ifndef __BULLET_HANDLER__
#define __BULLET_HANDLER__

#include <iostream>
#include <vector>
#include "PlayerBullet.h"
#include "EnemyBullet.h"

class BulletHandler {

public:

    static BulletHandler* get_instance()
    {
        if (sp_instance == 0)
        {
            sp_instance = new BulletHandler();
        }
        return sp_instance;
    }

    void add_player_bullet(int x, int y, int w, int h, std::string texture_id, 
        int num_frames, Vector2D heading);
    void add_enemy_bullet(int x, int y, int w, int h, std::string texture_id, 
        int num_frames, Vector2D heading);
    void update_bullets();
    void draw_bullets();

    void clear_bullets();

    const std::vector<PlayerBullet*> get_player_bullets() { return m_player_bullets; }
    const std::vector<EnemyBullet*> get_enemy_bullets() { return m_enemy_bullets; }



private:
    BulletHandler();
    ~BulletHandler();

    BulletHandler(const BulletHandler&);
    BulletHandler& operator=(BulletHandler&);

    static BulletHandler* sp_instance;

    //in play bullets
    std::vector<PlayerBullet*> m_player_bullets;
    std::vector<EnemyBullet*> m_enemy_bullets;
};

typedef BulletHandler BulletHdlr;

#endif /* __BULLET_HANDLER__ */