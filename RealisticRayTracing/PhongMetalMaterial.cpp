#include "PhoneMetalMaterial.h"
#include "Texture.h"

rgb PhongMetalMaterial::AmbientResponse(const ONB &, const Vector3 &, const Vector3 &p, const Vector2 &uv)
{
	return R->Value(uv, p);
}

bool PhongMetalMaterial::SpecularDirection(const ONB &uvw, const Vector3 &v_in, const Vector3 &p, const Vector2 &uv, Vector2 &seed, rgb &color, Vector3 &v_out)
{
	float pi = 3.1415926535f;
	float phi = 2 * pi*seed.x;
	float exponent = phong_exp->Value(uv, p).r;
	float cosTheta = pow(1 - seed.y, 1.f / (exponent + 1));
	float sinTheta = sqrt(1 - cosTheta*cosTheta);
	float x = cos(phi)*sinTheta;
	float y = sin(phi)*sinTheta;
	float z = cosTheta;

	ONB basis;
	Vector3 w = v_in - 2 * Dot(v_in, uvw.w)*uvw.w;
	basis.InitFromW(w);

	color = R->Value(uv, p);
	v_out = x*basis.u + y*basis.v + z*basis.w;

	if (exponent < 10000) seed.Scramble();
	return (Dot(v_out, uvw.w) > 0);
}