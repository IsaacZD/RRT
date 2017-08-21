#include "Ray.h"
#include "Image.h"
#include "Shape.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Sample.h"
#include "Camera.h"
#include "MarbleTexture.h"
#include "NoiseTexture.h"
#include "DynSphere.h"

#define OUTPUT_PATH "E:/WorkSpaces/VS2017/test.ppm"

int main()
{
	MarbleTexture marbleTex(.05f);
	NoiseTexture noiseTex(rgb(1.f, 1.f, 1.f), rgb(0.f, 0.f, .5f), .01f);

	Shape* s[]
	{
		new DynSphere(Vector3(0.f, 0.f, -20.f), 2.f, &marbleTex, 0.f, 5.f)
		//new Sphere(Vector3(-5, -5, -30), 10, &marbleTex),
		//new Triangle(Vector3(300, 600, -800), Vector3(0, 100, -1000), Vector3(450, 20, -1000), &noiseTex)
	};

	Camera camera(
		Vector3(0.0f, 0.0f, 0.0f), Vector3(0, 0, -1.0f), Vector3(0.0f, 1.0f, 0.0f),
		1.f, -20.f, 20.f, -20.f, 20.f, 30.f
	);

	Image image(500, 500);
	float tmin;
	rgb color;
	Vector2 samples[100];
	Vector2 sample_lens[100];
	for (int t = 0; t < 5; t++)
	{
		for(int i = 0; i<500; i++)
			for (int j = 0; j < 500; j++)
			{
				color.r = color.g = color.b = 0.f;
				HitRecord rec;
				MultiJitter(samples, sizeof(samples)/sizeof(Vector2));
				CubicSplineFilter(samples, sizeof(samples)/sizeof(Vector2));
				Jitter(sample_lens, sizeof(sample_lens) / sizeof(Vector2));
				int a = 0;
				for (Vector2 &sample : samples)
				{
					//Ray r(Vector3(i+sample.x, j+sample.y, 0), Vector3(0, 0, -1));
					Ray r = camera.GetRay(double(i + sample.x)/500., double(j + sample.y)/500., sample_lens[a].x, sample_lens[a].y);
					rgb tempColor;
					tmin = 10000.f;
					for (Shape* shape : s)
					{
						if(shape->Hit(r, 0.1f, tmin, float(t)/5, rec))
							if (rec.t < tmin) { tmin = rec.t; tempColor = rec.texture->Value(Vector2(), rec.pos); }
					}
					color += tempColor;
					a++;
				}
				image.Set(i, j, color/sizeof(samples)*sizeof(Vector2));
				std::cout << "\b\b\b\b\b" << i / 5 << "%";
			}
	}
	std::ofstream of(OUTPUT_PATH, ios::binary);
	image.WritePPM(of);
	of.close();

	return 0;
}