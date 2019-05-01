#ifndef __TILE_LAYER_H__
#define __TILE_LAYER_H__
#include <vector>

#include "Game.h"
#include "TextureManager.h"
#include "Vector2D.h"
#include "Layer.h"
#include "Level.h"


class TileLayer : public Layer
{

public:
	typedef TextureManager TextureMgr;
	TileLayer(int, const std::vector<Tileset>&);
	virtual void render();
	virtual void update();

	void set_tile_ids(std::vector<std::vector<int>>& data);
	void set_tile_size(int tile_size);

	Tileset get_tileset_by_id(int id);

	int get_tile_size() { return m_tile_size; }
	const std::vector<std::vector<int>>& get_tile_ids() { return m_tile_ids; }
	const Vector2D get_position() { return m_pos; }

private:
	
	int m_num_cols;
	int m_num_rows;
	int m_tile_size;
	int m_map_width;

	const std::vector<Tileset>& m_tilesets;
	std::vector<std::vector<int>> m_tile_ids;

	Vector2D m_pos;
	Vector2D m_vel;

	

};

#endif /* __LAYER_H__ */