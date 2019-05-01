#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <iostream>
#include <vector>
#include "Layer.h"
#include "LevelParser.h"
#include "Player.h"
#include "CollisionManager.h"

class TileLayer;

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

	~Level() {}

	void update();
	void render();
	std::vector<Tileset>* get_tilesets();
	std::vector<Layer*>* get_layers();

	Player* get_player() { return m_player; }
	void set_player(Player* p_player) { m_player = p_player; }
	std::vector<TileLayer*>* get_collision_layers() { return &m_collision_layers; }
	std::vector<TileLayer*>& get_collidable_layers() { return m_collision_layers; }

private:
	friend class LevelParser;
	Level();

	std::vector<Tileset> m_tilesets;
	std::vector<Layer*> m_layers;
	std::vector<TileLayer*> m_collision_layers;
	Player* m_player;
};

#endif /*__LEVEL_H__*/