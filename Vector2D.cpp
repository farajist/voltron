#include "Vector2D.h"
//TODO: reimplement operators using cpp primer advice, remove accessors 

Vector2D::Vector2D(float x, float y) : m_x(x), m_y(y)
{

}


float Vector2D::length()
{
	return sqrt(m_x * m_x + m_y * m_y);
}

Vector2D Vector2D::operator+(const Vector2D& v) const
{
	return Vector2D(m_x + v.m_x, m_y + v.m_y);
}

Vector2D Vector2D::operator-(const Vector2D& v) const
{
	return Vector2D(m_x - v.m_x, m_y - v.m_y);
}

Vector2D Vector2D::operator*(float scalar)
{	
	return Vector2D(m_x * scalar, m_y * scalar);
}

Vector2D Vector2D::operator/(float scalar)
{
	return Vector2D(m_x / scalar, m_y / scalar);
}

Vector2D& operator+=(Vector2D& v, const Vector2D& w)
{
	v.m_x += w.m_x;
	v.m_y += w.m_y;
	return v;
}

Vector2D& operator-=(Vector2D& v, const Vector2D& w)
{
	v.m_x -= w.m_x;
	v.m_y -= w.m_y;
	return v;
}

Vector2D& Vector2D::operator*=(float scalar)
{
	this->m_x *= scalar;
	this->m_y *= scalar;

	return *this;
}

Vector2D& Vector2D::operator/=(float scalar)
{
	this->m_x /= scalar;
	this->m_y /= scalar;

	return *this;
}

void Vector2D::normalize()
{
	float l = length();
	if (l > 0)
		(*this) *= 1 / l;
}