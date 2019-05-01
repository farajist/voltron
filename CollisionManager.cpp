#include "CollisionManager.h"

#include "Collision.h"
#include "Player.h"
#include "Enemy.h"
#include "BulletHandler.h"
#include "TileLayer.h"

void CollisionManager::check_player_enemy_bullet_collision(Player* p_player)
{
    SDL_Rect* p_rect_1 = new SDL_Rect();
    p_rect_1->x = p_player->get_position().get_x();
    p_rect_1->y = p_player->get_position().get_y();
    p_rect_1->w = p_player->get_width();
    p_rect_1->h = p_player->get_height();
    
    for(int i = 0; i < BulletHdlr::get_instance()->get_enemy_bullets().size(); i++)
    {
        EnemyBullet* p_enemy_bullet = BulletHdlr::get_instance()->get_enemy_bullets()[i];
        
        SDL_Rect* p_rect_2 = new SDL_Rect();
        p_rect_2->x = p_enemy_bullet->get_position().get_x();
        p_rect_2->y = p_enemy_bullet->get_position().get_y();
        
        p_rect_2->w = p_enemy_bullet->get_width();
        p_rect_2->h = p_enemy_bullet->get_height();
        
        if(RectRect(p_rect_1, p_rect_2))
        {
            if(!p_player->dying() && !p_enemy_bullet->dying())
            {
                p_enemy_bullet->collision();
                p_player->collision();
            }
        }
        
        delete p_rect_2;
    }
    
    delete p_rect_1;
}

void CollisionManager::check_enemy_player_bullet_collision(const std::vector<GameObject*> &objects)
{
     for(int i = 0; i < objects.size(); i++)
    {
        GameObject* p_object = objects[i];
        
        for(int j = 0; j < BulletHdlr::get_instance()->get_player_bullets().size(); j++)
        {
            if(p_object->type() != std::string("Enemy") || !p_object->updating())
            {
                continue;
            }
            
            SDL_Rect* p_rect_1 = new SDL_Rect();
            p_rect_1->x = p_object->get_position().get_x();
            p_rect_1->y = p_object->get_position().get_y();
            p_rect_1->w = p_object->get_width();
            p_rect_1->h = p_object->get_height();
            
            PlayerBullet* p_player_bullet = BulletHdlr::get_instance()->get_player_bullets()[j];
            
            SDL_Rect* p_rect_2 = new SDL_Rect();
            p_rect_2->x = p_player_bullet->get_position().get_x();
            p_rect_2->y = p_player_bullet->get_position().get_y();
            p_rect_2->w = p_player_bullet->get_width();
            p_rect_2->h = p_player_bullet->get_height();
            
            if(RectRect(p_rect_1, p_rect_2))
            {
                if(!p_object->dying() && !p_player_bullet->dying())
                {
                    p_player_bullet->collision();
                    p_object->collision();
                }
                
            }
            
            delete p_rect_1;
            delete p_rect_2;
        }
    }
}


void CollisionManager::check_player_enemy_collision(Player* p_player, const std::vector<GameObject*> &objects)
{
    SDL_Rect* p_rect_1 = new SDL_Rect();
    p_rect_1->x = p_player->get_position().get_x();
    p_rect_1->y = p_player->get_position().get_y();
    p_rect_1->w = p_player->get_width();
    p_rect_1->h = p_player->get_height();
    
    for(int i = 0; i < objects.size(); i++)
    {
        if(objects[i]->type() != std::string("Enemy") || !objects[i]->updating())
        {
            continue;
        }
        
        SDL_Rect* p_rect_2 = new SDL_Rect();
        p_rect_2->x = objects[i]->get_position().get_x();
        p_rect_2->y = objects[i]->get_position().get_y();
        p_rect_2->w = objects[i]->get_width();
        p_rect_2->h = objects[i]->get_height();
        
        if(RectRect(p_rect_1, p_rect_2))
        {
            if(!objects[i]->dead() && !objects[i]->dying())
            {
                p_player->collision();
            }
        }
        
        delete p_rect_2;
    }
    
    delete p_rect_1;
}

void CollisionManager::check_player_tile_collision(Player* p_player, const std::vector<TileLayer*> &collision_layers)
{
    for(std::vector<TileLayer*>::const_iterator it = collision_layers.begin(); it != collision_layers.end(); ++it)
    {
        TileLayer* p_tile_layer = (*it);
        std::vector<std::vector<int>> tiles = p_tile_layer->get_tile_ids();
        
        Vector2D layer_pos = p_tile_layer->get_position();
        
        int x, y, tileColumn, tileRow, tileid = 0;
        
        x = layer_pos.get_x() / p_tile_layer->get_tile_size();
        y = layer_pos.get_y() / p_tile_layer->get_tile_size();
        
        if(p_player->get_vel().get_x() >= 0 || p_player->get_vel().get_y() >= 0)
        {
            tileColumn = ((p_player->get_position().get_x() + p_player->get_width()) / p_tile_layer->get_tile_size());
            tileRow = ((p_player->get_position().get_y() + p_player->get_height()) / p_tile_layer->get_tile_size());
            tileid = tiles[tileRow + y][tileColumn + x];
        }
        else if(p_player->get_vel().get_x() < 0 || p_player->get_vel().get_y() < 0)
        {
            tileColumn = p_player->get_position().get_x() / p_tile_layer->get_tile_size();
            tileRow = p_player->get_position().get_y() / p_tile_layer->get_tile_size();
            tileid = tiles[tileRow + y][tileColumn + x];
        }
        
        if(tileid != 0)
        {
            p_player->collision();
        }
    }
}
