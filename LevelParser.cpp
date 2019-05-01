#include "LevelParser.h"

#include <string>
#include "LevelParser.h"
#include "TextureManager.h"
#include "Game.h"
#include "ObjectLayer.h"
#include "TileLayer.h"
#include "GameObjectFactory.h"
#include "base64.h"
#include "Level.h"

typedef TextureManager TextureMgr;
Level* LevelParser::parse_level(const char* level_file)
{
	tinyxml2::XMLDocument level_doc(true, tinyxml2::COLLAPSE_WHITESPACE);
	
	level_doc.LoadFile(level_file);

	//create the level object
	Level* p_level = new Level(); //_-_

	//get root node
	tinyxml2::XMLElement* p_root = level_doc.RootElement();

	m_tile_size = p_root->IntAttribute("tilewidth");
	m_width = p_root->IntAttribute("width");
	m_height = p_root->IntAttribute("height");

	//parse textures embedded inside the "properties" that's the first child of root
	//TODO: refactor .. just find optimal way
	tinyxml2::XMLElement* p_props = p_root->FirstChildElement();
	for (tinyxml2::XMLElement* e = p_props->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) 
	{
		if (!std::strcmp(e->Name(), "property"))
		{
			parse_textures(e);
		}
	}
	std::cout << "map texture have been successfully loaded !" << std::endl;
	
	//parse the tilesets
	for (tinyxml2::XMLElement* e = p_root->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (!std::strcmp(e->Name(), "tileset")){
			std::cout << "found tileset" << std::endl;
			parse_tilesets(e, p_level->get_tilesets());

		}
			
	}

	//parse any object layers
	for (tinyxml2::XMLElement* e = p_root->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (!std::strcmp(e->Name(), "layer") || !std::strcmp(e->Name(), "objectgroup"))
		{
			if (!std::strcmp(e->FirstChildElement()->Name(), "object"))
			{
				std::cout << "Found an object to parse !" << std::endl;
				parse_object_layer(e, p_level->get_layers(), p_level);
			} 
			else if (!std::strcmp(e->FirstChildElement()->Name(), "data") ||
						(e->FirstChildElement()->NextSiblingElement() != 0 && 
						!std::strcmp(e->FirstChildElement()->NextSiblingElement()->Name(), "data")))
			{
				parse_tile_layer(e, p_level->get_layers(), p_level->get_tilesets(),
				p_level->get_collision_layers());
			}
		}
	}

	return p_level;
}

void LevelParser::parse_tilesets(tinyxml2::XMLElement* ts_root, std::vector<Tileset>* p_tilesets)
{
	//add tileset to texture manager
	std::cout << "image path found is " << ts_root->FirstChildElement()->Attribute("source") << std::endl;
	TextureMgr::get_instance()->load(ts_root->FirstChildElement()->Attribute("source"), ts_root->Attribute("name"),
		Game::get_instance()->get_renderer());
		// std::cout << "parsed image width found is " << ts_root->FirstChildElement()->IntAttribute("width") << std::endl;
		// std::cout << "parsed image height found is " << ts_root->FirstChildElement()->IntAttribute("height") << std::endl;
		// std::cout << "tilewidth found is " << ts_root->IntAttribute("tilewidth") << std::endl;
		// std::cout << "tileheight found is " << ts_root->IntAttribute("tileheight") << std::endl;
		//create a tileset object
		Tileset tileset;
		tileset.width = ts_root->FirstChildElement()->IntAttribute("width");
		tileset.height = ts_root->FirstChildElement()->IntAttribute("height");
		tileset.first_gid = ts_root->IntAttribute("firstgid");
		tileset.tile_width = ts_root->IntAttribute("tilewidth");
		tileset.tile_height = ts_root->IntAttribute("tileheight");
		tileset.spacing = ts_root->IntAttribute("spacing");
		tileset.margin = ts_root->IntAttribute("margin");
		tileset.name = ts_root->Attribute("name");

		std::cout << "width :" << tileset.width << std::endl; 
		std::cout << "spacing|margin : " << tileset.spacing << "|" << tileset.margin << std::endl;
		std::cout << "tile_width :" << tileset.tile_width << std::endl; 
		tileset.num_cols = tileset.width / (tileset.tile_width + tileset.spacing);
		std::cout << "num_cols :" << tileset.num_cols << std::endl; 
		p_tilesets->push_back(tileset);
}

void LevelParser::parse_tile_layer(tinyxml2::XMLElement* p_tile_elt, std::vector<Layer*>* p_layers,
		const std::vector<Tileset>* p_tilesets, std::vector<TileLayer*> *p_collision_layers)
{
	TileLayer* p_tile_layer = new TileLayer(m_tile_size, *p_tilesets);
	bool collidable = false;
	//tile data 
	std::vector<std::vector<int>> data;
	std::string decoded_ids;
	tinyxml2::XMLElement *p_data_node;
	std::cout << "Commencing TileLayer parsing " << std::endl;
	for (tinyxml2::XMLElement* e = p_tile_elt->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (!std::strcmp(e->Name(), "properties"))
		{
			for (tinyxml2::XMLElement* prop = e->FirstChildElement(); prop != NULL; prop = prop->NextSiblingElement()) {
				if (!std::strcmp(prop->Value(), "property"))
				{
					if (!std::strcmp(prop->Attribute("name"), "collidable"))
					{
						collidable = true;
					}
				}
			}
		}
		if (!std::strcmp(e->Name(), "data")){
			p_data_node = e;
			// std::cout << "Found data node " << std::endl;
		}
			
	}

	//FIXME: why the loop ??
	//TODO: I guess there should really be a loop to avoid reading an empty string 
	for (tinyxml2::XMLNode* e = p_data_node->FirstChild(); e != NULL; e = e->NextSibling())
	{
		tinyxml2::XMLText* text = e->ToText();
		std::cout << "inside a for loop" << std::endl;
		std::string t = std::string(p_data_node->GetText());
		std::cout << "data node has content " << t << " size is " << t.size() << std::endl;
		decoded_ids = base64_decode(t);
		std::cout << "d3coded " << decoded_ids << std::endl;
	}
		
	// std::cout << "width : " << m_width << " height : " << m_height << std::endl; 

	//uncompress zlib compression
	uLongf num_gids = m_width * m_height * sizeof(int);
	//the size of the vector should be w x h normally a matrix -_-
	std::vector<unsigned> gids(m_width * m_height);
	
	uncompress((Bytef*)&gids[0], &num_gids, (const Bytef*) decoded_ids.c_str(),
	decoded_ids.size());

	std::vector<int> layer_row(m_width);
	//simply copies empty rows in each iteration to our data matrix
	for (int j = 0; j < m_height; ++j)
		data.push_back(layer_row);

	//this is the most important part where actual data is pushed to layer
	//strategy : fill matrix from array 
	for (int rows = 0; rows < m_height; ++rows)
	{
		for (int cols = 0; cols < m_width; ++cols){
			data[rows][cols] = gids[rows*m_width + cols];
			// std::cout << " gids : " << gids[rows*m_width + cols];
		}
			
	}

	// for (int rows = 0; rows < m_height; ++rows)
	// {
	// 	for (int cols = 0; cols < m_width; ++cols){
	// 		std::cout << data[rows][cols] << " "; 
	// 	}
	// 	std::cout << std::endl;
	// }

	//data now contains tile ids for the layer
	p_tile_layer->set_tile_ids(data);
	p_layers->push_back(p_tile_layer);
}

void LevelParser::parse_textures(tinyxml2::XMLElement* p_prop) 
{
	TextureMgr::get_instance()->load(p_prop->Attribute("value"),
	p_prop->Attribute("name"), Game::get_instance()->get_renderer());
}

void LevelParser::parse_object_layer(tinyxml2::XMLElement *p_object_element, std::vector<Layer*>* p_layers, Level* p_level)
{
	//create an object layer
	ObjectLayer* p_object_layer = new ObjectLayer();

	std::cout << p_object_element->FirstChildElement()->Name() << std::endl;	

	for (tinyxml2::XMLElement* e = p_object_element->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		std::cout << e->Name();
		std::cout << e;
		if (!std::strcmp(e->Name(), "object"))
		{
			std::cout << "commencing object parsing " << std::endl;
			int x, y, width, height, num_frames, callback_id, anim_speed;
			std::string texture_id, type;

			//get the initial node values
			x = e->IntAttribute("x");
			y = e->IntAttribute("y");

			type = e->Attribute("type");
			GameObject* p_game_object = GameObjectFactory::get_instance()->create(type);
			std::cout << "x|y : " << x << y << std::endl;  
			// GameObject* p_game_object = GameObjectFactory::get_instance()->create(e->Attribute("type"));
			std::cout << "parsing rest of the props : " << std::endl;  
			//get prop values
			for (tinyxml2::XMLElement* props = e->FirstChildElement(); props != NULL; props = props->NextSiblingElement())
			{
				if (!std::strcmp(props->Name(), "properties")) 
				{
					std::cout << "props detected : " << std::endl;  
					// NOTE: prop wasn't assigned in the increment part of the next loop => cause 
					for (tinyxml2::XMLElement* prop = props->FirstChildElement(); prop != NULL; prop = prop->NextSiblingElement())
					{
						if (!std::strcmp(prop->Name(), "property"))
						{
							std::cout << "prop detected : " << std::endl; 
							if (!std::strcmp(prop->Attribute("name"), "num_frames"))
							{
								num_frames = prop->IntAttribute("value");
								std::cout << "num_frames : " << num_frames << std::endl; 
							}
							else if (!std::strcmp(prop->Attribute("name"), "texture_height"))
							{
								height = prop->IntAttribute("value");
							}
							else if (!std::strcmp(prop->Attribute("name"), "texture_width"))
							{
								width = prop->IntAttribute("value");
							}
							else if (!std::strcmp(prop->Attribute("name"), "texture_id"))
							{
								texture_id = prop->Attribute("value");
							}
							else if (!std::strcmp(prop->Attribute("name"), "callback_id"))
							{
								callback_id = prop->IntAttribute("value");
							}
							else if (!std::strcmp(prop->Attribute("name"), "anim_speed"))
							{
								anim_speed = prop->IntAttribute("value");
							}
						}
					}
				}
			}
			std::cout << "width|height : " << width << height << std::endl;  
			std::cout << "texture_id|num_frames|callback_id : " << texture_id << num_frames << callback_id << height << std::endl;
			p_game_object->load(std::unique_ptr<LoaderParams>(new LoaderParams(x, y, width, height, texture_id, num_frames, callback_id, anim_speed)));

			if (type == "Player") {
				p_level->set_player(dynamic_cast<Player*>(p_game_object));
			}
			p_object_layer->get_game_objects()->push_back(p_game_object);
		}
	}
	std::cout << "object parsing complete" << std::endl;
	p_layers->push_back(p_object_layer);
	std::cout << "object parsing complete" << std::endl;
}