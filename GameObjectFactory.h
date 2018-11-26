#ifndef __GAME_OBJECT_FACTORY__
#define __GAME_OBJECT_FACTORY__

#include <string>
#include <map>

#include "GameObject.h"

class BaseCreator
{
public:
	virtual GameObject* create_game_object() const = 0;
	virtual ~BaseCreator() {}
};

class GameObjectFactory 
{
public:
	static GameObjectFactory* get_instance();
	bool register_type(std::string type_id, BaseCreator* p_creator);
	GameObject* create(std::string type_id);

private:
	GameObjectFactory() {}
	~GameObjectFactory() {}

	static GameObjectFactory *p_instance;
	std::map<std::string, BaseCreator*> m_creators;
};
#endif /* __GAME_OBJECT_FACTORY__ */