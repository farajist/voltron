#ifndef __LEVEL_PARSER_H__
#define __LEVEL_PARSER_H__

#include<tinyxml2.h>
#include<zlib.h>

#include "base64.h"
#include "Game.h"
#include "TextureManager.h"
#include "Level.h"
#include "TileLayer.h"


class LevelParser
{
public:
	typedef TextureManager TextureMgr;
	Level* parse_level(const char*);

private:
	void parse_tilesets(tinyxml2::XMLElement* ts_root, std::vector<Tileset>*);
	void parse_tile_layer(tinyxml2::XMLElement* p_tile_elt, std::vector<Layer*>*,
		const std::vector<Tileset>*);
	int m_tile_size;
	int m_width;
	int m_height;
};
#endif /*__LEVEL_PARSER_H__*/