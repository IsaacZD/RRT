#pragma once

#include <cmath>
#include "Vector3.h"

class SolidNoise
{
public:
	SolidNoise();
	float Noise(const Vector3 &) const;
	float Turbulence(const Vector3 &p, int depth) const;
	float DTurbulence(const Vector3 &p, int depth, float d) const;
	float Omega(float t) const;
	Vector3 Gamma(int i, int j, int k) const;
	int IntGamma(int i, int j) const;
	float Knot(int i, int j, int k, Vector3 &v) const;

public:
	Vector3 grad[16];
	int phi[16];
};

inline float SolidNoise::Omega(float t) const
{
	t = (t > 0.0f) ? t : -t;
	return (-6.0f*t*t*t*t*t + 15.0f*t*t*t*t - 10.0f*t*t*t + 1.0f);
}

inline Vector3 SolidNoise::Gamma(int i, int j, int k) const
{
	int idx;
	idx = phi[abs(k) % 16];
	idx = phi[abs(j + idx) % 16];
	idx = phi[abs(i + idx) % 16];
	return grad[idx];
}

inline float SolidNoise::Knot(int i, int j, int k, Vector3 &v) const
{
	return (Omega(v.x)*Omega(v.y) * Omega(v.z) * (Dot(Gamma(i, j, k), v)));
}

inline int SolidNoise::IntGamma(int i, int j) const
{
	int idx;
	idx = phi[abs(j) % 16];
	idx = phi[abs(i + idx) % 16];
	return idx;
}
