#include "DiffuseMaterial.h"
#include "Texture.h"

rgb DiffuseMaterial::AmbientResponse(const ONB &, const Vector3 &, const Vector3 &p, const Vector2 &uv)
{
	return R->Value(uv, p);
}

bool DiffuseMaterial::ExplicitBRDF(const ONB &, const Vector3 &, const Vector3 &, const Vector3 &p, const Vector2 &uv, rgb &brdf)
{
	float k = .318309886184f; // 1.0/PI
	brdf = k*R->Value(uv, p);
	return true;
}

bool DiffuseMaterial::DiffuseDirection(const ONB &uvw, const Vector3 &, const Vector3 &p, const Vector2 &uv, Vector2 &seed, rgb &color, Vector3 &v_out)
{
	float pi = 3.1415926535f;
	float phi = 2 * pi*seed.x;
	float r = sqrt(seed.y);
	float x = r*cos(phi);
	float y = r*sin(phi);
	float z = sqrt(1 - x*x - y*y);

	color = R->Value(uv, p);
	v_out = x*uvw.u + y*uvw.v + z*uvw.w;

	seed.Scramble();
	return true;
}