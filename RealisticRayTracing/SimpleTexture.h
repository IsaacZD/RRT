#pragma once
#ifndef _SIMPLE_TEXTURE_H_
#define _SIMPLE_TEXTURE_H_

#include "Texture.h"

class SimpleTexture : public Texture
{
public:
	SimpleTexture(rgb c) : color(c) { }
	virtual rgb Value(const Vector2 &, const Vector3 &) const override { return color; }

public:
	rgb color;
};


#endif // !_SIMPLE_TEXTURE_H_

