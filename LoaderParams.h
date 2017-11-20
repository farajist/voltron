#ifndef __LOADER_PARAMS__
#define __LOADER_PARAMS__

/*TODO: really get urself a .cpp ??*/
#include <string>

class LoaderParams
{
public:
	LoaderParams(int x, int y, int w, int h,
		std::string id) : m_x(x), m_y(y), m_width(w), m_height(h),
		m_texture_id(id)
		{

		}

	int get_x() const { return m_x; }
	int get_y() const { return m_y; }
	int get_width() const { return m_width; }
	int get_height() const { return m_height; }
	std::string get_texture_id() const { return m_texture_id; }

private:

	int m_x;
	int m_y;

	int m_width;
	int m_height;

	std::string m_texture_id;
};


#endif /* __LOADER_PARAMS__ */