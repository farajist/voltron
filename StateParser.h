#ifndef __STATE_PARSER_H__
#define __STATE_PARSER_H__

#include<iostream>
#include<vector>
#include<string>
#include<tinyxml.h>

#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
class StateParser
{
public:
	typedef TextureManager TextureMgr;

	bool parse_state(const char* state_file, std::string state_id,
		std::vector<GameObject*> *, std::vector<std::string> *);
private:
	void parse_objects(TiXmlElement*, std::vector<GameObject*> *);
	void parse_textures(TiXmlElement*, std::vector<std::string> *);
};

#endif /* __STATE_PARSER_H__ */