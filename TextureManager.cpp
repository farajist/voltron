#include "TextureManager.h"

TextureManager* TextureManager::sp_instance = nullptr;

bool TextureManager::load(std::string filename, std::string id, SDL_Renderer* p_renderer)
{
	SDL_Surface *p_temp_surface = IMG_Load(filename.c_str());

	//surface failed to load
	if (p_temp_surface == NULL) 
		return false;

	SDL_Texture *p_texture = SDL_CreateTextureFromSurface(p_renderer, p_temp_surface);
	SDL_FreeSurface(p_temp_surface);

	//everthing ok, texture loaded !
	if (p_texture != NULL)
	{
		m_texture_map[id] = p_texture;
		return true;
	}

	//something went wrong
	return false;
}

//draw : takes x,y of dest rect, h,w of src rect, flip value and a renderer
void TextureManager::draw(std::string id, int x, int y, int width, int height, 
		SDL_Renderer* p_renderer, SDL_RendererFlip flip)
{
	SDL_Rect src_rect;
	SDL_Rect dest_rect;

	//render will start from this coordinate of the texture
	src_rect.x = 0;
	src_rect.y = 0;

	//renderer will render src_rect.hxsrc_rect.w of the given texture, ofc 
	//surface that will be rendered at is dest_rect !
	src_rect.w = dest_rect.w = width;
	src_rect.h = dest_rect.h = height;

	dest_rect.x = x;
	dest_rect.y = y;

	SDL_RenderCopyEx(p_renderer, m_texture_map[id], &src_rect, &dest_rect, 0, 0, flip);
}

//draw frame : additional params, current frame to draw and its row in the ss
void TextureManager::draw_frame(std::string id, int x, int y, int width, int height,
		int curr_row, int curr_frame, SDL_Renderer *p_renderer, 
		SDL_RendererFlip flip)
{
	//reaaaaaaallllly needs a private function to leverage work in draw/draw_frame

	SDL_Rect src_rect;
	SDL_Rect dest_rect;

	src_rect.x = width * curr_frame;
	src_rect.y = height * (curr_row - 1);

	src_rect.w = dest_rect.w = width;
	src_rect.h = dest_rect.h = height;

	dest_rect.x = x;
	dest_rect.y = y;

	SDL_RenderCopyEx(p_renderer, m_texture_map[id], &src_rect, &dest_rect, 0, 0, flip);	
}

TextureManager* TextureManager::get_instance() {
	if (sp_instance == nullptr)
	{
		sp_instance = new TextureManager();
		return sp_instance;
	}
	return sp_instance;
}

void TextureManager::clear_from_texture_map(std::string id)
{
	m_texture_map.erase(id);
}