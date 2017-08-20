#include "MarbleTexture.h"

rgb MarbleTexture::Value(const Vector2 &uv, const Vector3 &pos) const
{
	float temp = scale * noise.Turbulence(freq*pos, octaves);
	float t = 2.0f * fabs(sin(freq*pos.x + temp));

	if (t < 1.0f)
		return (c1*t + (1.0f - t)*c2);
	else
	{
		t -= 1.0f;
		return (c0*t + (1.0f - t)*c1);
	}
}