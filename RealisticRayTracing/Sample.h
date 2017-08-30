#pragma once

#include <cmath>

class Vector2;

void Random(Vector2 *samples, int num);

void Jitter(Vector2 *samples, int num);

void Nrooks(Vector2 *samples, int num);

void MultiJitter(Vector2 *samples, int num);

void Shuffle(Vector2 *samples, int num);

void BoxFilter(Vector2 *samples, int num);

void TentFilter(Vector2 *samples, int num);

void CubicSplineFilter(Vector2 *samples, int num);

void Random(float *samples, int num);

void Jitter(float *samples, int num);

void Shuffle(float *samples, int num);

inline float Solve(float r)
{
	float u = r;
	for (int i = 0; i < 5; i++)
		u = (11.0f*r + u*u*(6.0f + u*(8.0f - 9.0f*u))) / (4.0f + 12.0f*u*(1.0f + u*(1.0f - u)));
	return u;
}

inline float CubicFilter(float x)
{
	if (x < 1.0f / 24.0f)
		return pow(24 * x, 0.25f) - 2.0f;
	else if (x < 0.5f)
		return Solve(24.0f*(x - 1.0f / 24.0f) / 11.0f) - 1.0f;
	else if (x < 23.0f / 24.0f)
		return 1.0f - Solve(24.0f*(23.0f / 24.0f - x) / 11.0f);
	else return 2 - pow(24.0f*(1.0f - x), 0.25f);
}
