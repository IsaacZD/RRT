#pragma once

#include <cmath>
#include "Texture.h"
#include "rgb.h" 
#include "SolidNoise.h"

class NoiseTexture : public Texture
{
public:
	NoiseTexture(float scale = 1.0f) : scale(scale), c0(0.8, 0.0, 0.0), c1(0.0, 0.0, 0.8) { }

	NoiseTexture(const rgb &c0, const rgb &c1, float scale = 1.0f)
		: scale(scale), c0(c0), c1(c1) { }

	virtual rgb Value(const Vector2 &uv, const Vector3 &pos) const override;

public:
	float scale;
	rgb c0, c1;
	SolidNoise solid_noise;
};

