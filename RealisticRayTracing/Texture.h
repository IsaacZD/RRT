#pragma once
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "Vector2.h"
#include "Vector3.h"
#include "rgb.h"

class Texture
{
public:
	virtual rgb Value(const Vector2 &uv, const Vector3 &pos) const = 0;
};


#endif // !_TEXTURE_H_

