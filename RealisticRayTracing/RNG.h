#pragma once

class RNG
{
public:
	RNG(unsigned long long seed = 7564231ULL) :
		seed(seed), mult(62089911ULL), llong_max(4294967295ULL),
		float_max(4294967295.0f) { }

	float operator()();


public:
	unsigned long long seed;
	unsigned long long mult;
	unsigned long long llong_max;
	float float_max;
};

inline float RNG::operator()()
{
	seed *= mult;
	return float(seed%llong_max) / float_max;
}
