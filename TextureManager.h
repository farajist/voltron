#ifndef __TEXTURE_MANAGER__
#define __TEXTURE_MANAGER__

#include <iostream>
#include <string>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class TextureManager {

public:
	bool load(std::string filename, std::string id, SDL_Renderer* p_renderer);

	//draw : takes x,y of dest rect, h,w of src rect, flip value and a renderer
	void draw(std::string id, int x, int y, int width, int height, 
		SDL_Renderer* p_renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	//draw frame : additional params, current frame to draw and its row in the ss
	void draw_frame(std::string, int x, int y, int width, int height,
		int curr_row, int curr_frame, SDL_Renderer *p_renderer, 
		double angle, int alpha, SDL_RendererFlip flip = SDL_FLIP_NONE);


	void draw_tile(std::string name, int margin, int spacing, int x, int y,
	 	int width, int height, int curr_row, int curr_frame, 
		SDL_Renderer* p_renderer);
		
	void clear_from_texture_map(std::string id);
	static TextureManager* get_instance();
private:
	TextureManager() {}
	static TextureManager* sp_instance;
	std::map<std::string, SDL_Texture*> m_texture_map;
};

#endif /*__TEXTURE_MANAGER__*/