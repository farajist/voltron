#include "Player.h"

Player::Player() : ShooterObject(),
m_invulnerable(false),
m_invulnerable_time(200),
m_invulnerable_counter(0)
{
}

void Player::collision()
{
	//if the player is not invulnerable then set to dying and change values 
	//for death animation tile sheet
	if(!m_invulnerable && !Game::get_instance()->get_level_complete())
    {
        m_texture_id = "largeexplosion";
        m_curr_frame = 0;
        m_num_frames = 9;
        m_width = 60;
        m_height = 60;
        mb_dying = true;
    }
}

void Player::draw()
{
	ShooterObject::draw();
}
void Player::resurrect()
{
	
}

void Player::handle_animation() 
{
	//if player is invulnerable we can flash its alpha to let people know
	if (m_invulnerable) 
	{
		if (m_invulnerable_counter == m_invulnerable_time)
		{
			m_invulnerable = false;
			m_invulnerable_counter = 0;
			m_alpha = 255;
		}
		else 
		{
			if (m_alpha == 255) 
			{
				m_alpha = 0;
			}
			else 
			{
				m_alpha = 255;
			}

			//increment our counter
			m_invulnerable_counter++;
		}
		//if the player is not dead then we can change the angle with the 
		//velocity to give the impression of a moving helicopter
		if (!mb_dead)
		{
			if (m_vel.get_x() < 0)
			{
				m_angle = -10.0;
			}
			else if (m_vel.get_x() > 0)
			{
				m_angle = 10.0;
			}
			else 
			{
				m_angle = 0.0;
			}
		}
		//our standard animation code - for helicopter propellors
		m_curr_frame = int(((SDL_GetTicks() / 100) % m_num_frames));
	}
}

void Player::update() 
{
	//if the level is complete then fly off the screen
	if (Game::get_instance()->get_level_complete())
	{
		if (m_pos.get_x() >= Game::get_instance()->get_width())
		{
			Game::get_instance()->set_current_level(Game::get_instance()
				->get_current_level() + 1);
		}
		else 
		{
			m_vel.set_y(0);
			m_vel.set_x(3);
			ShooterObject::update();
			handle_animation();
		}
	}
	else
	{
		//if the player isn't doing death animation .update normally
		if (!mb_dying)
		{
			//reset velocity
			m_vel.set_x(0);
			m_vel.set_y(0);

			//get input
			handle_input();
			// do normal pos += vel update
			ShooterObject::update();

			//update the animation
			handle_animation();
		} else
		{
			// if player is dying 
			m_curr_frame = int(((SDL_GetTicks() / 100)) % m_num_frames);
			//if the death animation has completed
			if (m_dying_counter == m_dying_time)
			{
				resurrect();
			}
			m_dying_counter++;
		}
		
	}
}

void Player::clean()
{
	ShooterObject::clean();
	// std::cout << "Player's clean function called !" << std::endl;
}

void Player::handle_input() 
{
	 if(!mb_dead)
    {
        // handle keys
        if(InputHandler::get_instance()->is_key_down(SDL_SCANCODE_UP) && m_pos.get_y() > 0)
        {
            m_vel.set_y(-m_move_speed);
        }
        else if(InputHandler::get_instance()->is_key_down(SDL_SCANCODE_DOWN) && (m_pos.get_y() + m_height) < Game::get_instance()->get_height() - 10)
        {
            m_vel.set_y(m_move_speed);
        }
        
        if(InputHandler::get_instance()->is_key_down(SDL_SCANCODE_LEFT) && m_pos.get_x() > 0)
        {
            m_vel.set_x(-m_move_speed);
        }
        else if(InputHandler::get_instance()->is_key_down(SDL_SCANCODE_RIGHT) && (m_pos.get_x() + m_width) < Game::get_instance()->get_width())
        {
            m_vel.set_x(m_move_speed);
        }
        
        if(InputHandler::get_instance()->is_key_down(SDL_SCANCODE_SPACE))
        {
            if(m_bullet_counter == m_bullet_firing_speed)
            {
                SoundMgr::get_instance()->play_sound("shoot", 0);
				BulletHdlr::get_instance()->add_player_bullet(m_pos.get_x() + 90, m_pos.get_y() + 12, 11, 11, "bullet1", 1, Vector2D(10,0));
                m_bullet_counter = 0;
            }
            
            m_bullet_counter++;
        }
        else
        {
            m_bullet_counter = m_bullet_firing_speed;
        }
        // */
        
        /* handle joysticks /
        if(TheInputHandler::Instance()->joysticksInitialised())
        {
            if(TheInputHandler::Instance()->getButtonState(0, 2))
            {
                if(m_bulletCounter == m_bulletFiringSpeed)
                {
                    TheSoundManager::Instance()->playSound("shoot", 0);
                    TheBulletHandler::Instance()->addPlayerBullet(m_position.getX() + 90, m_position.getY() + 12, 11, 11, "bullet1", 1, Vector2D(10,0));
                    m_bulletCounter = 0;
                }
                
                m_bulletCounter++;
            }
            else
            {
                m_bulletCounter = m_bulletFiringSpeed;
            }
            
            if((TheInputHandler::Instance()->getAxisX(0, 1) > 0 && (m_position.getX() + m_width) < TheGame::Instance()->getGameWidth()) || (TheInputHandler::Instance()->getAxisX(0, 1) < 0 && m_position.getX() > 0))
            {
                m_velocity.setX(m_moveSpeed * TheInputHandler::Instance()->getAxisX(0, 1));
            }
            
            if((TheInputHandler::Instance()->getAxisY(0, 1) > 0 && (m_position.getY() + m_height) < TheGame::Instance()->getGameHeight() - 10 ) || (TheInputHandler::Instance()->getAxisY(0, 1) < 0 && m_position.getY() > 0))
            {
                m_velocity.setY(m_moveSpeed * TheInputHandler::Instance()->getAxisY(0, 1));
            }
        }
        //*/
        
    }
}