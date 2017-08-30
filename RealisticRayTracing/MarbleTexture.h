#pragma once

#include <cmath>
#include "Texture.h"
#include "rgb.h"
#include "SolidNoise.h"

const float PI = 3.1415926f;

class MarbleTexture : public Texture
{
public:
	MarbleTexture(float stripes_per_unit, float scale = 5.0f, int octaves = 8)
		: freq(PI*stripes_per_unit), scale(scale), octaves(octaves), 
		c0(0.8f, 0.8f, 0.8f), c1(0.4f, 0.2f, 0.1f), c2(0.06f, 0.04f, 0.02f) { }
	MarbleTexture(const rgb &c0, const rgb &c1, const rgb &c2,
		float stripes_per_unit, float scale = 3.0f, int octaves = 8)
		: freq(PI*stripes_per_unit), scale(scale), octaves(octaves) { }

	virtual rgb Value(const Vector2 &uv, const Vector3 &pos) const;


public:
	float freq, scale;
	int octaves;
	rgb c0, c1, c2;
	SolidNoise noise;
};
