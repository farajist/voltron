#ifndef __COLLISION_MANAGER__
#define __COLLISION_MANAGER__
#include <vector>

class Player;
class GameObject;
class TileLayer;

class CollisionManager
{

public:
    void check_player_enemy_bullet_collision(Player* p_player);
    void check_player_enemy_collision(Player* p_player, const std::vector<GameObject*> &objects);
    void check_enemy_player_bullet_collision(const std::vector<GameObject*> &objects);
    void check_player_tile_collision(Player* p_player, const std::vector<TileLayer*> &collision_layers);
};
#endif /* __COLLISION_MANAGER__ */