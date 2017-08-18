#pragma once
#ifndef _VECTOR2_H_
#define _VECTOR2_H_

class Vector2
{
public:
	Vector2() { }
	Vector2(float x, float y) : x(x), y(y) { }

	Vector2& operator=(const Vector2 &vec) { x = vec.x; y = vec.y; return *this; }

public:
	float x, y;

};

#endif // !_VECTOR2_H_

