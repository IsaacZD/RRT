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
#include "PhoneMetalMaterial.h"
#include "UVSphere.h"
#include "Instance.h"
#include <ctime>
#include "BVH.h"

#define OUTPUT_PATH "E:/WorkSpaces/VS2017/test.png"
#define CANEXCUTE false

void render(const Camera &camera, int width, const BVH &root, int nsamples, char *path);

const Vector3 cc(0.f, 0.f, -13.f);
const float cl= 10.f;

const float intensity = 5.0f;
const int max_depth = 10;

const int num_samples = 1600;
const int image_size = 800;

int main()
{
	srand(time(nullptr));
	SimpleTexture white(rgb(1.f, 1.f, 1.f));
	SimpleTexture black((rgb()));
	SimpleTexture red(rgb(1.f, .0f, .0f));
	SimpleTexture green(rgb(.0f, 1.f, .0f));
	SimpleTexture blue(rgb(.0f, .0f, 1.f));
	SimpleTexture gray(rgb(.75f));
	SimpleTexture lightred(rgb(.75f, .25f, .25f));
	SimpleTexture lightblue(rgb(.25f, .25f, .75f));

	SimpleTexture refl(rgb(0.999f));
	SimpleTexture phong(rgb(16.f));

	ImageTexture image("color.ppm");

	DiffuseMaterial rm(&red);
	DiffuseMaterial gm(&green);
	DiffuseMaterial bm(&blue);

	DiffuseMaterial lrm(&lightred);
	DiffuseMaterial lbm(&lightblue);

	DiffuseMaterial graym(&gray);
	DiffuseMaterial blackm(&black);
	DiffuseMaterial im(&image);

	PhongMetalMaterial pmm(&refl, &phong);

	// if delete the parentheses around the constructor, the compiler(VS2017)
	// would treat the constructor as a declaration. WHY???
	EmitMaterial em( (rgb(intensity)) );

	Mesh mesh;
	mesh.material = &graym;
	mesh.vertUVs = new VertexUV[8]{
		{Vector3(cc.x + cl, cc.y + cl, cc.z - cl), Vector2()},
		{Vector3(cc.x - cl, cc.y + cl, cc.z - cl), Vector2()},
		{Vector3(cc.x - cl, cc.y + cl, cc.z + 2*cl), Vector2()},
		{Vector3(cc.x + cl, cc.y + cl, cc.z + 2*cl), Vector2()},

		{Vector3(cc.x + cl, cc.y - cl, cc.z - cl), Vector2()},
		{Vector3(cc.x - cl, cc.y - cl, cc.z - cl), Vector2()},
		{Vector3(cc.x - cl, cc.y - cl, cc.z + 2*cl), Vector2()},
		{Vector3(cc.x + cl, cc.y - cl, cc.z + 2*cl), Vector2()}
	};

	Shape *shapes[] = {
		//new Triangle(Vector3(cc.x-cl/2, cc.y+cl-.00001f, cc.z-cl/2), Vector3(cc.x+cl/2, cc.y+cl-.00001f, cc.z-cl/2), Vector3(cc.x+cl/2, cc.y+cl-.00001f, cc.z+cl/2), &em),
		//new Triangle(Vector3(cc.x-cl/2, cc.y+cl-.00001f, cc.z-cl/2), Vector3(cc.x+cl/2, cc.y+cl-.00001f, cc.z+cl/2), Vector3(cc.x-cl/2, cc.y+cl-.00001f, cc.z+cl/2), &em),

		//new Sphere(Vector3(0.f, 1250.f+cl-0.01f, cc.z), 1250.f, &em),
		new Sphere(Vector3(0.f, 5.f, -5), 3.f, &em),
		new UVSphere(Vector3(-3.f, -5.f, -7.f), 3.f, &pmm),
		new Sphere(Vector3(3.f, -5.f, -6.f), 3.f, &gm),

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

	Camera camera(Vector3(0.f, 0.f, 7.f), Vector3(0.f, 0.f, -1.f), Vector3(0.f, 1.f, 0.f), .1f, -7.f, 7.f, -7.f, 7.f, 7.f);

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
		if (rec.material->DiffuseDirection(rec.uvw, ray.d, rec.tex_pos, rec.uv, seed, color, d) ||
			rec.material->SpecularDirection(rec.uvw, ray.d, rec.tex_pos, rec.uv, seed, color, d))
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
	image.WritePNG(outfile);
	outfile.close();
}
