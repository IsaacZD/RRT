#include "Ray.h"
#include "Image.h"
#include "Shape.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Sample.h"
#include "Camera.h"

int main()
{
	Shape* s[]
	{
		new Sphere(Vector3(250, 250, -1000), 150, rgb(1.0f, 0.0f, 0.0f)),
		new Triangle(Vector3(300, 600, -800), Vector3(0, 100, -1000), Vector3(450, 20, -1000), rgb(0.5f, 0.5f, 0.5f))
	};

	Camera camera(
		Vector3(0.0f, 0.0f, 0.0f), Vector3(0, 0, -1.0f), Vector3(0.0f, 1.0f, 0.0f),
		0.5f, -5.f, 5.f, -5.f, 5.f, 10.f
	);

	Image image(500, 500);
	float tmin;
	rgb color;
	Vector2 samples[9];
	Vector2 sample_lens[9];

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
				tmin = 5000.f;
				for (Shape* shape : s)
				{
					shape->Hit(r, 0.1f, 5000.f, 0.f, rec);
					if (rec.t < tmin) { tmin = rec.t; tempColor = rec.color; }
				}
				color += tempColor;
				a++;
			}
			image.Set(i, j, color/sizeof(samples)*sizeof(Vector2));
			cout << "\b\b\b\b\b" << i / 5 << "%";
		}
	std::ofstream of("E:/WorkSpaces/VS2017/test.ppm", ios::binary);
	image.WritePPM(of);
	of.close();

	return 0;
}