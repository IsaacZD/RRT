#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "rgb.h"

class Texture
{
public:
	virtual rgb Value(const Vector2 &uv, const Vector3 &pos) const = 0;
};
