#ifndef __VECTOR_2D__
#define __VECTOR_2D__

#include <cmath>
class Vector2D
{
public:
	Vector2D(float x, float y);

	float get_x() {return this->m_x;}
	float get_y() {return this->m_y;}

	void set_x(float x) {this->m_x = x;}
	void set_y(float y) {this->m_y = y;}

	float length();
	
	Vector2D operator+(const Vector2D&) const;
	friend Vector2D& operator+=(Vector2D&, const Vector2D&);

	Vector2D operator-(const Vector2D&) const;
	friend Vector2D& operator-=(Vector2D&, const Vector2D&);


	Vector2D operator*(float);
	Vector2D& operator*=(float);

	Vector2D operator/(float);
	Vector2D& operator/=(float);

	void normalize();

private:
	float m_x;
	float m_y;
	
};

Vector2D& operator+=(Vector2D&, const Vector2D&);
Vector2D& operator-=(Vector2D&, const Vector2D&);
// Vector2D& operator*=(float);
// Vector2D& operator/=(float);
#endif /* __VECTOR_2D__ */