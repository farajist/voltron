#include "ScrollingBackground.h"
#include "TextureManager.h"
#include "Game.h"

ScrollingBackground::ScrollingBackground(): ShooterObject()
{
    count = 0;
    max_count = 10;
}

void ScrollingBackground::load(std::unique_ptr<LoaderParams> const &p_params)
{
    ShooterObject::load(std::move(p_params));
    m_scroll_speed = p_params->get_anim_speed();

    m_scroll_speed = 1;
    m_src_rect1.x = 0;
    m_dest_rect1.x = m_pos.get_x();
    m_src_rect1.y = 0;
    m_dest_rect1.y = m_pos.get_y();

    m_src_rect1.w = m_dest_rect1.w = m_src_rect2_w = m_dest_rect1_w = m_width;
    m_src_rect1.h = m_dest_rect1.h = m_height;

    m_src_rect2.x = 0;
    m_dest_rect2.x = m_pos.get_x() + m_width;
    m_src_rect2.y = 0;
    m_dest_rect2.y = m_pos.get_y();

    m_src_rect2.w = m_dest_rect2.w = m_src_rect2_w = m_dest_rect2_w = 0;
    m_src_rect2.h = m_dest_rect2.h = m_height;
}

void ScrollingBackground::draw()
{

}

void ScrollingBackground::update()
{
    if (count == max_count)
    {
        //make the first rectangle smaller
        m_src_rect1.x += m_scroll_speed;
        m_src_rect1.w -= m_scroll_speed;
        m_dest_rect1.w -= m_scroll_speed;

        //make second rectangle bigger
        m_src_rect2.w += m_scroll_speed;
        m_dest_rect2.w += m_scroll_speed;
        m_dest_rect2.x -= m_scroll_speed;

        //reset and start again
        if (m_dest_rect2.w >= m_width)
        {
            m_src_rect1.x = 0;
            m_dest_rect1.x = m_pos.get_x();
            m_src_rect1.y = 0;
            m_dest_rect1.y = m_pos.get_y();

            m_src_rect1.w = m_dest_rect1.w = m_src_rect2_w = m_dest_rect1_w = m_width;
            m_src_rect1.h = m_dest_rect1.h = m_height;

            m_src_rect2.x = 0;
            m_dest_rect2.x = m_pos.get_x() + m_width;
            m_src_rect2.y = 0;
            m_dest_rect2.y = m_pos.get_y();

            m_src_rect2.w = m_dest_rect2.w = m_src_rect2_w = m_dest_rect2_w = 0;
            m_src_rect2.h = m_dest_rect2.h = m_height;
        }
        count = 0;
    }
    count++;
}

void ScrollingBackground::clean()
{
    ShooterObject::clean();
}