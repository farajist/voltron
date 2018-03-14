#ifndef __LOADER_PARAMS__
#define __LOADER_PARAMS__

/*TODO: really get urself a .cpp ??*/
#include <string>

class LoaderParams
{
public:
	LoaderParams(int x, int y, int w, int h,
		std::string id, int nf, int cid = 0, int as = 0) 
		: m_x(x), m_y(y), m_width(w), m_height(h),
		m_num_frames(nf), m_texture_id(id),
		m_callback_id(cid), m_anim_speed(as)
{

}

	int get_x() const { return m_x; }
	int get_y() const { return m_y; }
	int get_width() const { return m_width; }
	int get_height() const { return m_height; }
	std::string get_texture_id() const { return m_texture_id; }
	int get_num_frames() const { return m_num_frames; }

	int get_callback_id() const { return m_callback_id; }
	int get_anim_speed() const { return m_anim_speed; }

private:

	int m_x;
	int m_y;

	int m_width;
	int m_height;

	int m_num_frames;
	std::string m_texture_id;

	int m_callback_id;
	int m_anim_speed;

};


#endif /* __LOADER_PARAMS__ */