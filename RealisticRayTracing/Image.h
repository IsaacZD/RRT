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
	void ReadPPM(string file_name);

private:
	rgb** raster;
	int width, height;
};

