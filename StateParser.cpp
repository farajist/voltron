#include "StateParser.h"


bool StateParser::parse_state(const char* state_file, std::string state_id,
		std::vector<GameObject*> *p_objects, std::vector<std::string> *p_texture_ids)
{
	// printf("Value of state is %s", state_id.c_str());	
	TiXmlDocument xmlDoc;
	//loading state file
	if (!xmlDoc.LoadFile("test.xml"))
	{
		std::cout << xmlDoc.ErrorDesc() << std::endl;
		return false;
	}
	xmlDoc.Print();
	std::cout << state_file << " loaded successfully !" << std::endl;
	
	TiXmlElement *p_root = xmlDoc.RootElement();

	if (p_root == nullptr) 
		std::cout << "root non-allowed value !" << std::endl;
	// TiXmlNode* child = 0;
	// while((child = p_root->IterateChildren( child ))){
	// 	std::cout << child->ValueStr() << std::endl;
	// }
	//pre declare state root node
	TiXmlElement *p_state_root = 0;
	std::cout << "Parsing state with ID : " << state_id << std::endl;
	
	//get state root node and assign it to p_state_root
	for (TiXmlElement* e = p_root->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if(e->ValueStr() == state_id)
		{
			p_state_root = e;
			break;
		}
			
	}
	std::cout << "State " << state_id << " parsed successfully !!" << std::endl;

	std::cout << "Parsing textures ..." << std::endl;

	if (p_state_root == nullptr) 
		std::cout << "state root non-allowed value !" << std::endl;
	//pre declate texture 
	TiXmlElement *p_textures_root = 0;
	
	//get root of texture elements
	for (TiXmlElement* e = p_state_root->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if(e->ValueStr() == std::string("TEXTURES"))
		{
			p_textures_root = e;
			break;
		}
			
	}

	//now lets parse textures
	this->parse_textures(p_textures_root, p_texture_ids);
	std::cout << "Parsed textures successfully !" << std::endl;
		
	std::cout << "Parsing game objects ..." << std::endl;
	//predeclare object root node
	TiXmlElement* p_object_root = 0;

	//get root node and assign it to p_object_root
	for (TiXmlElement* e = p_state_root->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if(e->ValueStr() == std::string("OBJECTS"))
		{
			p_object_root = e;
			break;
		}
			
	}
	
	//now parse objects
	this->parse_objects(p_object_root, p_objects);
	std::cout << "Parsed game objects successfully !" << std::endl;
	//everything good ?
	return true;
}



void StateParser::parse_objects(TiXmlElement* p_object_root, std::vector<GameObject*> *p_objects)
{
	for (TiXmlElement* e = p_object_root->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		int x, y, w, h, nf, cid, as;
		std::string texture_id;

		e->Attribute("x", &x);
		e->Attribute("y", &y);
		e->Attribute("width", &w);
		e->Attribute("height", &h);
		e->Attribute("num_frames", &nf);
		e->Attribute("callback_id", &cid);
		e->Attribute("anim_speed", &as);

		texture_id = e->Attribute("texture_id");

		GameObject* p_go = GameObjectFactory::get_instance()
			->create(e->Attribute("type"));
		p_go->load(new LoaderParams(x, y, w, h, texture_id, nf, cid, as));
		p_objects->push_back(p_go);
	}
}


void StateParser::parse_textures(TiXmlElement* p_texture_root, 
						std::vector<std::string> *p_texture_ids) 
{

	for (TiXmlElement* e = p_texture_root->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		std::string filename_attr = e->Attribute("filename");
		std::string id_attr = e->Attribute("ID");
		p_texture_ids->push_back(id_attr); //push id into list

		TextureMgr::get_instance()->load(filename_attr, id_attr, Game::get_instance()->get_renderer());
	}
}