#ifndef __LEVEL_PARSER_H__
#define __LEVEL_PARSER_H__

#include<tinyxml2.h>
#include<zlib.h>
#include <vector>

// #include "base64.h"
// #include "Game.h"
// #include "TextureManager.h"
// // #include "Level.h"
// // #include "TileLayer.h"
// #include "ObjectLayer.h"


class Level;
struct Tileset;
class Layer;
class TileLayer;

class LevelParser
{
public:

	Level* parse_level(const char*);

private:
	void parse_tilesets(tinyxml2::XMLElement* ts_root, std::vector<Tileset>*);

	void parse_tile_layer(tinyxml2::XMLElement* p_tile_elt, std::vector<Layer*>*,
		const std::vector<Tileset>*, std::vector<TileLayer*> *p_collision_layers);
	void parse_textures(tinyxml2::XMLElement* p_texture_root);
	void parse_object_layer(tinyxml2::XMLElement* p_object_element, std::vector<Layer*>* p_layers, Level* p_level);
	int m_tile_size;
	int m_width;
	int m_height;
};
#endif /*__LEVEL_PARSER_H__*/