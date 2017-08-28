#pragma once
#ifndef _VECTOR2_H_
#define _VECTOR2_H_

class Vector2
{
public:
	Vector2() : x(0.f), y(0.f) { }
	Vector2(float x, float y) : x(x), y(y) { }

	Vector2& operator=(const Vector2 &vec) { x = vec.x; y = vec.y; return *this; }

public:
	float x, y;

};

inline Vector2 operator-(const Vector2 &lhs, const Vector2 &rhs) { return Vector2(lhs.x-rhs.x, lhs.y-rhs.y); }

inline Vector2 operator+(const Vector2 &lhs, const Vector2 &rhs) { return Vector2(lhs.x + rhs.x, lhs.y + rhs.y); }

inline Vector2 operator*(const Vector2 &v, float s)
{
	return Vector2(v.x*s, v.y*s);
}

inline Vector2 operator*(float s, const Vector2 &v)
{
	return Vector2(v.x*s, v.y*s);
}

#endif // !_VECTOR2_H_

