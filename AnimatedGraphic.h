#ifndef __ANIMATED_GRAPHIC__
#define __ANIMATED_GRAPHIC__

#include "ShooterObject.h"
#include "LoaderParams.h"
#include "GameObjectFactory.h"

class AnimatedGraphic : public ShooterObject
{
public:

	AnimatedGraphic();
	void draw();
	void update();
	void clean();

	virtual void load(std::unique_ptr<LoaderParams> const&);

private:
	int m_anim_speed;
};


class AnimatedGraphicCreator : public BaseCreator
{
	GameObject* create_game_object() const 
	{
		return new AnimatedGraphic();
	}
};

#endif /* __ANIMATED_GRAPHIC__ */