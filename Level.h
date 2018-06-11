#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <vector>
#include <string>

#include "Layer.h"

struct Tileset
{
	int first_gid;
	int tile_width;
	int tile_height;
	int spacing;
	int margin;
	int width;
	int height;
	int num_cols;
	std::string name;
};

class Level
{
public:
	friend class LevelParser;
	Level();
	~Level() {}

	void update();
	void render();
	std::vector<Tileset>* get_tilesets();
	std::vector<Layer*>* get_layers();

private:
	std::vector<Tileset> m_tilesets;
	std::vector<Layer*> m_layers;
};

#endif /*__LEVEL_H__*/