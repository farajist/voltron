#include "LevelParser.h"


Level* LevelParser::parse_level(const char* level_file)
{
	TiXmlDocument level_doc;
	level_doc.LoadFile(level_file);

	//create the level object
	Level* p_level = new Level(); //_-_

	//get root node
	TiXmlElement* p_root = level_doc.RootElement();

	p_root->Attribute("tilewidth", &m_tile_size);
	p_root->Attribute("width", &m_width);
	p_root->Attribute("height", &m_height);

	//parse the tilesets
	for (TiXmlElement* e = p_root->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->ValueStr() == std::string("tileset"))
			parse_tilesets(e, p_level->get_tilesets());
	}


	//parse any object layers
	for (TiXmlElement* e = p_root->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->ValueStr() == std::string("layer"))
			parse_tile_layer(e, p_level->get_layers(), p_level->get_tilesets());
	}

	return p_level;
}

void LevelParser::parse_tilesets(TiXmlElement* ts_root, std::vector<Tileset>* p_tilesets)
{
	//add tileset to texture manager
	TextureMgr::get_instance()->load(ts_root->FirstChildElement()->Attribute("source"), ts_root->Attribute("name"),
		Game::get_instance()->get_renderer());

		//create a tileset object
		Tileset tileset;
		ts_root->FirstChildElement()->Attribute("width", &tileset.width);
		ts_root->FirstChildElement()->Attribute("height", &tileset.height);
		ts_root->Attribute("firstgid", &tileset.first_gid);
		ts_root->Attribute("tilewidth", &tileset.width);
		ts_root->Attribute("tileheight", &tileset.height);
		ts_root->Attribute("spacing", &tileset.spacing);
		ts_root->Attribute("margin", &tileset.margin);
		tileset.name = ts_root->Attribute("name");

		tileset.num_cols = tileset.width / (tileset.tile_width + tileset.spacing);
		p_tilesets->push_back(tileset);
}

void LevelParser::parse_tile_layer(TiXmlElement* p_tile_elt, std::vector<Layer*>* p_layers,
		const std::vector<Tileset>* p_tilesets)
{
	TileLayer* p_tile_layer = new TileLayer(m_tile_size, *p_tilesets);

	//tile data 
	std::vector<std::vector<int>> data;
	std::string decoded_ids;
	TiXmlElement *p_data_node;

	for (TiXmlElement* e = p_tile_elt->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->ValueStr() == std::string("data"))
			p_data_node = e;
	}

	for (TiXmlNode* e = p_data_node->FirstChild(); e != NULL; e = e->NextSiblingElement())
	{
		TiXmlText* text = e->ToText();
		std::string t = text->ValueStr();
		decoded_ids = base64_decode(t);
	}

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
		for (int cols = 0; cols < m_width; ++cols)
			data[rows][cols] = gids[rows*m_width + cols];
	}

	//data now contains tile ids for the layer
	p_tile_layer->set_tile_ids(data);
	p_layers->push_back(p_tile_layer);
}