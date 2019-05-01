#include "BulletHandler.h"
#include "Game.h"


BulletHandler* BulletHandler::sp_instance = new BulletHandler();

BulletHandler::BulletHandler()
{
}

void add_player_bullet(int x, int y, int w, int h, std::string texture_id, 
        int num_frames, Vector2D heading)
{
    PlayerBullet *p_player_bullet = new PlayerBullet();
    p_player_bullet->load(std::unique_ptr<LoaderParams>(new  LoaderParams(x, y, w, h, texture_id, num_frames)), heading);
    m_player_bullets.push_back(p_player_bullet);
}

void add_enemy_bullet(int x, int y, int w, int h, std::string texture_id, 
        int num_frames, Vector2D heading)
{
    EnemyBullet *p_enemy_bullet = new EnemyBullet();
    p_enemy_bullet->load(std::unique_ptr<LoaderParams>(new  LoaderParams(x, y, w, h, texture_id, num_frames)), heading);
    m_enemy_bullets.push_back(p_enemy_bullet);   
}


void BulletHandler::clear_bullets()
{
    m_enemy_bullets.clear();
    m_player_bullets.clear();
}

void BulletHandler::update_bullets()
{
    for (std::vector<PlayerBullet*>::iterator p_it = m_player_bullets.begin(); p_it != m_player_bullets.end();)
    {
        if ((*p_it)->get_position().get_x() < 0 || (*p_it)->get_position().get_x() > Game::get_instance()->get_width()
        || (*p_it)->get_position().get_y() < 0 || (*p_it)->get_position().get_y() > Game::get_instance()->get_height() || (*p_it)->dead())
        {
            delete *p_it;
            p_it = m_player_bullets.erase(p_it);
        }
        else 
        {
            (*p_it)->update();
            ++p_it;
        }

    for (std::vector<EnemyBullet*>::iterator e_it = m_enemy_bullets.begin(); e_it != m_enemy_bullets.end();)
    {
        if ((*e_it)->get_position().get_x() < 0 || (*e_it)->get_position().get_x() > Game::get_instance()->get_width()
        || (*e_it)->get_position().get_y() < 0 || (*e_it)->get_position().get_y() > Game::get_instance()->get_height() || (*e_it)->dead())
        {
            delete *e_it;
            e_it = m_enemy_bullets.erase(e_it);
        }
        else 
        {
            (*e_it)->update();
            ++e_it;
        }
    }
}

void BulletHandler::draw_bullets()
{
    for (int p = 0; p < m_player_bullets.size(); p++)
    {
        m_player_bullets[p]->draw();
    }

    for (int e = 0; e < m_enemy_bullets.size(); e++)
    {
        m_enemy_bullets[e]->draw();
    }
}