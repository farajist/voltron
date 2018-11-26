#ifndef __LEVEL_PARSER_H__
#define __LEVEL_PARSER_H__

#include<tinyxml.h>
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
	void parse_tilesets(TiXmlElement*, std::vector<Tileset>*);
	void parse_tile_layer(TiXmlElement*, std::vector<Layer*>*,
		const std::vector<Tileset>*);
	int m_tile_size;
	int m_width;
	int m_height;
};
#endif /*__LEVEL_PARSER_H__*/