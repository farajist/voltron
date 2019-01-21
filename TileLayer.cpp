#include "TileLayer.h"

TileLayer::TileLayer(int tile_size, const std::vector<Tileset> &tilesets) : 
m_tile_size(tile_size), m_tilesets(tilesets), m_pos(0, 0), m_vel(0,0)
{
	/* 
	the size is provided in the parser, which is logical. number of cols and 
	rows in the tilelayer is calculated as follows
	*/
	m_num_cols = Game::get_instance()->get_width() / m_tile_size;
	m_num_rows = Game::get_instance()->get_height() / m_tile_size;
}

void TileLayer::render()
{
	int a, b, x, y = 0;

	// get me the coordinates of the position 
	// tile-wise, returns coordinates of the tile
	// a float that is trumcated
	//HACK: % m_num_cols did it !!!
	a = int(m_pos.get_x() / m_tile_size) % m_num_cols;
	b = m_pos.get_y() / m_tile_size;

	//we get the truncated part into x and y => always 0
	x = int(m_pos.get_x()) % m_tile_size;
	y = int(m_pos.get_y()) % m_tile_size;
	//for each row and each column
	for (int i = 0; i < m_num_rows; i++)
	{
		for (int j = 0; j < m_num_cols; j++)
		{
			//get the id of the tiles starting a's value to the right
			int id = m_tile_ids[i + b][j + a];
			if (id == 0)
				continue;
			Tileset tileset = get_tileset_by_id(id);
			// std::cout << "tileset data fgid: " << tileset.first_gid << " ncols : " << tileset.num_cols << std::endl;
			id--; //WHY ???? need a full scenario
			//params 2 and 3 are for spacing and margin
			//params 4 and 5 are the x and y for dest rect :
			//get the x pos we're in and substract the 
			//floating part  (x) you get the x of where you should 
			//start drawing, same for y
			// for the row and frame apply the fgid=180, id=203 please ! It's headache 
			// and i have an exam tomorrow => it gives you row and col in that picture of blocks
			// those are the curr_row/curr_frame needed by the tmgr's draw_tile
			//finally the renderer

			TextureMgr::get_instance()->draw_tile(tileset.name, tileset.margin, tileset.spacing, 
			(j * m_tile_size) - x, (i * m_tile_size) - y, m_tile_size,
			m_tile_size, (id - (tileset.first_gid - 1)) / tileset.num_cols,
			(id - (tileset.first_gid - 1)) % tileset.num_cols,
			Game::get_instance()->get_renderer());
		}
	}
}

void TileLayer::update()
{
	m_pos += m_vel;
	m_vel.set_x(2);
}

void TileLayer::set_tile_ids(std::vector<std::vector<int>>& data)
{
	this->m_tile_ids = data;
}
void TileLayer::set_tile_size(int tile_size)
{
	this->m_tile_size = tile_size;
}

Tileset TileLayer::get_tileset_by_id(int id)
{
	for (std::size_t i = 0; i < m_tilesets.size(); ++i)
	{
		if (i + 1 <= m_tilesets.size() -1)
		{
			if (id >= m_tilesets[i].first_gid && id < m_tilesets[i + 1].first_gid)
			{
				return m_tilesets[i];
			}
		}
		else
		{
			return m_tilesets[i];
		}
	}
	std::cout << "did not find tileset, returning empty tileset\n";
	Tileset t;
	return t;
}
