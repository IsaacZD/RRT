#pragma once

#include <cmath>
#include <string>
#include <fstream>
#include "rgb.h"
using namespace std;

class Image
{
public:
	Image();
	Image(int width, int height);
	Image(int width, int height, rgb background);

	bool Set(int x, int y, const rgb &color);
	void GammaCorrect(float gamma);
	void WritePPM(ostream &out);
	void WritePNG(ostream &out);
	void ReadPPM(string file_name);
	int Width() const { return width; }
	int Height() const { return height; }
	rgb *const operator[](int i) const { return raster[i]; }
	rgb *operator[](int i) { return raster[i]; }

private:
	rgb** raster;
	int width, height;
};

