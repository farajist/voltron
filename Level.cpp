#include "Level.h"

Level::Level()
{

}

void Level::update()
{
	for (Layer*& l : m_layers)
		l->update();
}

void Level::render()
{
	for (Layer*& l : m_layers)
		l->render();
}

std::vector<Tileset>* Level::get_tilesets()
{
	return &m_tilesets;
}

std::vector<Layer*>* Level::get_layers()
{
	return &m_layers;
}
