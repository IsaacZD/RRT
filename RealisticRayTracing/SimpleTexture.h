#pragma once

#include "Texture.h"

class SimpleTexture : public Texture
{
public:
	SimpleTexture(rgb c) : color(c) { }
	virtual rgb Value(const Vector2 &, const Vector3 &) const override { return color; }

public:
	rgb color;
};

