#include "ObjectLayer.h"

void ObjectLayer::update()
{
    for (GameObject*& go : m_game_objects)
        go->update();
}

void ObjectLayer::render() 
{
    for (GameObject*& go : m_game_objects)
        go->draw();
}