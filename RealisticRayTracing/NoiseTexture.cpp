#include "NoiseTexture.h"

rgb NoiseTexture::Value(const Vector2 &uv, const Vector3 &pos) const
{
	float t = (1.0f + solid_noise.Noise(pos*scale)) / 2.0f;
	return t*c0 + (1.0f - t)*c1;
}
