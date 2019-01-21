#include "LevelParser.h"


Level* LevelParser::parse_level(const char* level_file)
{
	tinyxml2::XMLDocument level_doc;
	level_doc.LoadFile(level_file);

	//create the level object
	Level* p_level = new Level(); //_-_

	//get root node
	tinyxml2::XMLElement* p_root = level_doc.RootElement();

	m_tile_size = p_root->IntAttribute("tilewidth");
	m_width = p_root->IntAttribute("width");
	m_height = p_root->IntAttribute("height");

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
		if (!std::strcmp(e->Name(), "layer"))
			parse_tile_layer(e, p_level->get_layers(), p_level->get_tilesets());
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
		const std::vector<Tileset>* p_tilesets)
{
	TileLayer* p_tile_layer = new TileLayer(m_tile_size, *p_tilesets);

	//tile data 
	std::vector<std::vector<int>> data;
	std::string decoded_ids;
	tinyxml2::XMLElement *p_data_node;
	std::cout << "Commencing TileLayer parsing " << std::endl;
	for (tinyxml2::XMLElement* e = p_tile_elt->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (!std::strcmp(e->Name(), "data")){
			p_data_node = e;
			// std::cout << "Found data node " << std::endl;
		}
			
	}

	//FIXME: why the loop ??
	// for (tinyxml2::XMLElement* e = p_data_node->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	// {
		// tinyxml2::XMLText* text = e->ToText();
		// std::cout << "inside a for loop" << std::endl;
		std::string t = std::string(p_data_node->GetText());
		// std::cout << "data node has content " << t << " size is " << t.size() << std::endl;
		decoded_ids = base64_decode(t);
		// std::cout << "d3coded " << decoded_ids << std::endl;
	// }

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

	for (int rows = 0; rows < m_height; ++rows)
	{
		for (int cols = 0; cols < m_width; ++cols){
			std::cout << data[rows][cols] << " "; 
		}
		std::cout << std::endl;
	}

	//data now contains tile ids for the layer
	p_tile_layer->set_tile_ids(data);
	p_layers->push_back(p_tile_layer);
}
