#include "Ray.h"
#include "Image.h"
#include "Shape.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Vector3.h"

int main()
{
	Shape* s[]
	{
		new Sphere(Vector3(250, 250, -1000), 150, rgb(1.0f, 0.0f, 0.0f)),
		new Triangle(Vector3(300, 600, -800), Vector3(0, 100, -1000), Vector3(450, 20, -1000), rgb(0.5f, 0.5f, 0.5f))
	};

	Image image(500, 500);
	float tmin;
	rgb color;

	for(int i = 0; i<500; i++)
		for (int j = 0; j < 500; j++)
		{
			tmin = 5000.f;
			Ray r(Vector3(i, j, 0), Vector3(0, 0, -1));
			HitRecord rec;
			for (Shape* shape : s)
			{
				shape->Hit(r, 0.1f, 5000.f, 0.f, rec);
				if (rec.t < tmin) { tmin = rec.t; color = rec.color; }
			}
			image.Set(i, j, color);
		}
	std::ofstream of("E:/WorkSpaces/VS2017/test.ppm", ios::binary);
	image.WritePPM(std::cout);
	of.close();

	return 0;
}