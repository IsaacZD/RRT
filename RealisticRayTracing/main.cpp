#include "Ray.h"
#include "Image.h"
#include "Mesh.h"
#include "MeshTriangle.h"
#include "Shape.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Sample.h"
#include "Camera.h"
#include "MarbleTexture.h"
#include "SimpleTexture.h"
#include "DiffuseMaterial.h"
#include "EmitMaterial.h"
#include "NoiseTexture.h"
#include "DynSphere.h"
#include "ImageTexture.h"
#include "UVTriangle.h"
#include "UVSphere.h"
#include "Instance.h"
#include <ctime>
#include "BVH.h"

#define OUTPUT_PATH "E:/WorkSpaces/VS2017/test.ppm"
#define CANEXCUTE false

void render(const Camera &camera, int width, const BVH &root, int nsamples, char *path);

const Vector3 cc(0.f, 0.f, -30.f);
const float cl= 20.f;

const float intensity = 1.f;
const int max_depth = 10;

const int num_samples = 900;
const int image_size = 500;

int main()
{
	srand(time(nullptr));
	SimpleTexture red(rgb(1.f, .0f, .0f));
	SimpleTexture green(rgb(.0f, 1.f, .0f));
	SimpleTexture blue(rgb(.0f, .0f, 1.f));
	SimpleTexture gray(rgb(.8f, .8f, .8f));
	ImageTexture image("color.ppm");

	DiffuseMaterial rm(&red);
	DiffuseMaterial gm(&green);
	DiffuseMaterial bm(&blue);
	DiffuseMaterial graym(&gray);
	DiffuseMaterial im(&image);

	// if delete the parentheses around the constructor, the compiler(VS2017)
	// would treat the constructor as a declaration. WHY???
	EmitMaterial em( (rgb(intensity)) );

	Mesh mesh;
	mesh.material = &graym;
	mesh.vertUVs = new VertexUV[8]{
		{Vector3(cc.x + cl, cc.y + cl, cc.z - cl), Vector2()},
		{Vector3(cc.x - cl, cc.y + cl, cc.z - cl), Vector2()},
		{Vector3(cc.x - cl, cc.y + cl, cc.z + 5*cl), Vector2()},
		{Vector3(cc.x + cl, cc.y + cl, cc.z + 5*cl), Vector2()},

		{Vector3(cc.x + cl, cc.y - cl, cc.z - cl), Vector2()},
		{Vector3(cc.x - cl, cc.y - cl, cc.z - cl), Vector2()},
		{Vector3(cc.x - cl, cc.y - cl, cc.z + 5*cl), Vector2()},
		{Vector3(cc.x + cl, cc.y - cl, cc.z + 5*cl), Vector2()}
	};

	Shape *shapes[] = {
		new Sphere(Vector3(0.f, 10.f, -30.f), 10.f, &em),
		new UVSphere(Vector3(0.f, -10.f, -30.f), 7.f, &gm),
		//new Sphere(Vector3(0.f, -50.f, -30.f), 33.f, &bm),

		new MeshTriangleUV(&mesh, 1, 0, 3, 0),
		new MeshTriangleUV(&mesh, 2, 1, 3, 0),
		new MeshTriangleUV(&mesh, 5, 1, 2, 0),
		new MeshTriangleUV(&mesh, 6, 5, 2, 0),
		new MeshTriangleUV(&mesh, 4, 0, 1, 0),
		new MeshTriangleUV(&mesh, 5, 4, 1, 0),
		new MeshTriangleUV(&mesh, 3, 0, 4, 0),
		new MeshTriangleUV(&mesh, 7, 3, 4, 0),
		new MeshTriangleUV(&mesh, 7, 4, 5, 0),
		new MeshTriangleUV(&mesh, 6, 7, 5, 0)
	};

	BVH root(shapes, sizeof(shapes)/sizeof(shapes[0]));

	Camera camera(Vector3(0.f, 0.f, -10.f), Vector3(0.f, 0.f, -1.f), Vector3(0.f, 1.f, 0.f), .1f, -20.f, 20.f, -20.f, 20.f, 10.f);

	render(camera, image_size, root, num_samples, OUTPUT_PATH);

	return 0;
}

rgb radiance(const BVH &root, Ray &ray, int depth=0)
{
	rgb rv;
	if (depth >= max_depth) return rv;
	HitRecord rec;
	if (root.Hit(ray, 0.001f, 5000.f, 0.f, rec))
	{
		Vector2 seed;
		seed.Scramble();
		rv += rec.material->EmittedRadiance(rec.uvw, -ray.d, rec.tex_pos, rec.uv);
		rgb color;
		Vector3 d;
		if (rec.material->DiffuseDirection(rec.uvw, ray.d, rec.tex_pos, rec.uv, seed, color, d))
		{
			ray.SetOrigin(rec.pos);
			ray.SetDirection(d);
			rv += color*radiance(root, ray, depth + 1);
		}
	}
	return rv;
}

void render(const Camera &camera, int image_width, const BVH &root, int nsamples, char *path)
{
	int width = camera.u1 - camera.u0;
	int height = camera.v1 - camera.v0;
	int image_height = image_width*height / width;
	double w = 1.0 / image_width;
	double h = 1.0 / image_height;
	double w100 = w*100;
	double s = 1.0 / nsamples;
	Image image(image_width, image_height);

	int i, j;
	for (i = 0; i < image_width; i++)
	{
#pragma omp parallel for
		for (j = 0; j < image_height; j++)
		{
			Vector2 *pixel_samples = new Vector2[nsamples];
			Vector2 *lens_samples = new Vector2[nsamples];
			rgb color;
			MultiJitter(pixel_samples, nsamples);
			CubicSplineFilter(pixel_samples, nsamples);
			Jitter(lens_samples, nsamples);
			Shuffle(lens_samples, nsamples);
			HitRecord rec;
			Vector2 *ps = pixel_samples, *ls = lens_samples;
			for(; ps!=pixel_samples+nsamples; ++ps, ++ls)
			{
				Ray ray = camera.GetRay((i+ps->x)*w, (j+ps->y)*h, ls->x, ls->y);
				color += radiance(root, ray);
			}
			image[i][j] = color*s;
			delete[] pixel_samples;
			delete[] lens_samples;
		}
		std::cout << "\b\b\b\b\b" << int(i*w100)  << "%";
	}
	
	ofstream outfile(path, ios::binary);
	image.WritePPM(outfile);
	outfile.close();
}
