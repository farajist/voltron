#include "GameObjectFactory.h"

GameObjectFactory* GameObjectFactory::p_instance = 0;

GameObjectFactory* GameObjectFactory::get_instance()
{
	if (p_instance == nullptr)
		p_instance = new GameObjectFactory();
	return p_instance;
}

bool GameObjectFactory::register_type(std::string type_id, BaseCreator* p_creator)
{
	auto it = m_creators.find(type_id);
	if (it != m_creators.end())
	{
		delete p_creator;
		return false;
	}
	m_creators[type_id] = p_creator;
	return true;
}

GameObject* GameObjectFactory::create(std::string type_id)
{
	auto it = m_creators.find(type_id);
	
	if (it == m_creators.end())
	{
		std::cout << "type not found : " << type_id << std::endl;
		return nullptr;
	}
	BaseCreator* p_creator = (*it).second;
	return p_creator->create_game_object();
}