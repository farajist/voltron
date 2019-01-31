#ifndef __OBJECT_LAYER_H__
#define __OBJECT_LAYER_H__
#include <vector>

#include "GameObject.h"
#include "Layer.h"

class ObjectLayer : public Layer 
{
public: 
    virtual void update();
    virtual void render();

    std::vector<GameObject*>* get_game_objects() {
        return &m_game_objects;
    }
private:
    std::vector<GameObject*> m_game_objects;
};

#endif /* __OBJECT_LAYER_H__ */
