#include "Sample.h"
#include "Vector2.h"
#include <cmath>

#define DRAND48() ((double)rand()/RAND_MAX)

void Random(Vector2 *samples, int num)
{
	for (int i = 0; i < num; i++)
	{
		samples[i].x = DRAND48();
		samples[i].y = DRAND48();
	}
}

void Jitter(Vector2 *samples, int num)
{
	int sqrt_samples = (int)(sqrt(num));

	for(int i = 0; i<sqrt_samples; i++)
		for (int j = 0; j < sqrt_samples; j++)
		{
			samples[i*sqrt_samples + j].x = ((double)i + DRAND48()) / (double)sqrt_samples;
			samples[i*sqrt_samples + j].y = ((double)j + DRAND48()) / (double)sqrt_samples;
		}
}

void Nrooks(Vector2 *samples, int num)
{
	for (int i = 0; i < num; i++)
	{
		samples[i].x = ((double)i + DRAND48()) / (double)num;
		samples[i].y = ((double)i + DRAND48()) / (double)num;
	}

	for (int i = num - 2; i >= 0; i--)
	{
		int target = int(DRAND48() * i);
		float temp = samples[i + 1].x;
		samples[i + 1].x = samples[target].x;
		samples[target].x = temp;
	}
}

void MultiJitter(Vector2 *samples, int num)
{
	int sqrt_samples = (int)sqrt(num);
	float subcell_width = 1.0f / (float(num));

	for(int i = 0; i<sqrt_samples; i++)
		for (int j = 0; j < sqrt_samples; j++)
		{
			samples[i*sqrt_samples + j].x = i*sqrt_samples*subcell_width + j*subcell_width + DRAND48()*subcell_width;
			samples[i*sqrt_samples + j].y = j*sqrt_samples*subcell_width + i*subcell_width + DRAND48()*subcell_width;
		}

	for(int i = 0; i<sqrt_samples; i++)
		for (int j = 0; j < sqrt_samples; j++)
		{
			int k = j + int(DRAND48() * (sqrt_samples - j - 1));
			float t = samples[i*sqrt_samples + j].x;
			samples[i*sqrt_samples + j].x = samples[i*sqrt_samples + k].x;
			samples[i*sqrt_samples + k].x = t;

			k = j + int(DRAND48()*(sqrt_samples - j - 1));
			t = samples[j*sqrt_samples + i].y;
			samples[j*sqrt_samples + i].y = samples[k*sqrt_samples + i].y;
			samples[k*sqrt_samples + i].y = t;
		}
}

void Shuffle(Vector2 *samples, int num)
{
	for (int i = num - 2; i >= 0; i--)
	{
		int target = int(DRAND48() * (double)i);
		Vector2 temp = samples[i + 1];
		samples[i + 1] = samples[target];
		samples[target] = temp;
	}
}

void BoxFilter(Vector2 *samples, int num)
{
	for (int i = 0; i < num; i++)
	{
		samples[i].x = samples[i].x - 0.5f;
		samples[i].y = samples[i].y - 0.5f;
	}
}

void TentFilter(Vector2 *samples, int num)
{
	for (int i = 0; i < num; i++)
	{
		float x = samples[i].x;
		float y = samples[i].y;
		
		if (x < 0.5f) samples[i].x = (float)sqrt(2.0*(double)x) - 1.0;
		else samples[i].x = 1.0f - (float)sqrt(2.0 - 2.0*(double)x);

		if (y < 0.5f) samples[i].y = (float)sqrt(2.0*(double)y) - 1.0f;
		else samples[i].y = 1.0f - (float)sqrt(2.0 - 2.0*(double)y);
	}
}

void CubicSplineFilter(Vector2 *samples, int num)
{
	for (int i = 0; i < num; i++)
	{
		float x = samples[i].x;
		float y = samples[i].y;

		samples[i].x = CubicFilter(x);
		samples[i].y = CubicFilter(y);
	}
}

void Random(float *samples, int num)
{
	for (int i = 0; i < num; i++)
		samples[i] = DRAND48();
}

void Jitter(float *samples, int num)
{
	for (int i = 0; i < num; i++)
		samples[i] = ((double)i + DRAND48()) / (double)num;
}

void Shuffle(float *samples, int num)
{
	for (int i = num- 2; i >= 0; i--)
	{
		int target = int(DRAND48()*(double)i);
		float temp = samples[i + 1];
		samples[i + 1] = samples[target];
		samples[target] = temp;
	}
}