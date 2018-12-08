#include "StateParser.h"


bool StateParser::parse_state(const char* state_file, std::string state_id,
		std::vector<GameObject*> *p_objects, std::vector<std::string> *p_texture_ids)
{
	// printf("Value of state is %s", state_id.c_str());	
	tinyxml2::XMLDocument xmlDoc;
	//loading state file
	if (xmlDoc.LoadFile("test.xml") != tinyxml2::XML_SUCCESS)
	{
		std::cout << xmlDoc.ErrorStr() << std::endl;
		return false;
	}
	std::cout << state_file << " loaded successfully !" << std::endl;
	
	tinyxml2::XMLElement *p_root = xmlDoc.RootElement();

	//pre declare state root node
	tinyxml2::XMLElement *p_state_root = nullptr;
	std::cout << "Parsing state with ID : " << state_id << std::endl;
	
	//get state root node and assign it to p_state_root
	for (tinyxml2::XMLElement* e = p_root->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if(!std::strcmp(e->Name(), state_id.c_str()))
		{
			p_state_root = e;
			break;
		}
	}

	std::cout << "Parsing textures ..." << std::endl;

	//pre declate texture 
	tinyxml2::XMLElement *p_textures_root = 0;
	
	//get root of texture elements
	for (tinyxml2::XMLElement* e = p_state_root->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if(!std::strcmp(e->Name(), "TEXTURES"))
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
	tinyxml2::XMLElement* p_object_root = 0;

	//get root node and assign it to p_object_root
	for (tinyxml2::XMLElement* e = p_state_root->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if(!std::strcmp(e->Name(), "OBJECTS"))
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



void StateParser::parse_objects(tinyxml2::XMLElement* p_object_root, std::vector<GameObject*> *p_objects)
{
	for (tinyxml2::XMLElement* e = p_object_root->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		int x, y, w, h, nf, cid, as;
		std::string texture_id;

		x = e->IntAttribute("x");
		y = e->IntAttribute("y");
		w = e->IntAttribute("width");
		h = e->IntAttribute("height");
		nf = e->IntAttribute("num_frames");
		cid = e->IntAttribute("callback_id");
		as = e->IntAttribute("anim_speed");

		texture_id = std::string(e->Attribute("texture_id"));

		GameObject* p_go = GameObjectFactory::get_instance()
			->create(e->Attribute("type"));
		p_go->load(new LoaderParams(x, y, w, h, texture_id, nf, cid, as));
		p_objects->push_back(p_go);
	}
}


void StateParser::parse_textures(tinyxml2::XMLElement* p_texture_root, 
						std::vector<std::string> *p_texture_ids) 
{

	for (tinyxml2::XMLElement* e = p_texture_root->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		std::string filename_attr = std::string(e->Attribute("filename"));
		std::string id_attr = std::string(e->Attribute("ID"));
		p_texture_ids->push_back(id_attr); //push id into list

		TextureMgr::get_instance()->load(filename_attr, id_attr, Game::get_instance()->get_renderer());
	}
}