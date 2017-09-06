#include "DielectricMaterial.h"
#include <cmath>

DielectricMaterial::DielectricMaterial(float nt, const rgb &ex)
	:nt(nt), extinction(ex)
{
	R0 = (nt - 1.0f) / (nt + 1.0f);
	R0 *= R0;

	extinction.r = log(extinction.r);
	extinction.g = log(extinction.g);
	extinction.b = log(extinction.b);
}

bool DielectricMaterial::SpecularDirection(const ONB &uvw,
	const Vector3 &in_dir,
	const Vector3 &texp,
	const Vector2 &uv,
	Vector2 &rseed,
	rgb &ratio,
	Vector3 &reflection)
{
	float scale;
	Vector3 normal = uvw.w;
	float cosine = Dot(in_dir, normal);

	if (cosine < 0.0f)
	{
		reflection = Reflect(in_dir, uvw.w);
		cosine = -cosine;
		float temp1 = 1.0f - cosine;
		scale = R0 + (1.0f - R0)*temp1*temp1*temp1*temp1*temp1;
	}
	else
	{
		reflection = Reflect(in_dir, -uvw.w);
		float temp2 = -(Dot(in_dir, -normal));
		float root = 1.0f - (nt*nt)*(1.0f - temp2*temp2);

		if (root < 0.0f) scale = 1.0f;
		else
		{
			float temp3 = 1.0f - cosine;
			scale = R0 + (1.0f - R0)*temp3*temp3*temp3*temp3*temp3;
		}
	}
	ratio = rgb(scale, scale, scale);
	return true;
}

bool DielectricMaterial::TransmissionDirection(const ONB &uvw,
	const Vector3 &in_dir,
	const Vector3 &texp,
	const Vector2 &uv,
	const Vector2 &rseed,
	rgb &_extinction,
	float &fresnel_scale,
	Vector3 &transmission)
{
	Vector3 normal = uvw.w;
	float cosine = Dot(in_dir, normal);

	if (cosine < 0.0f)
	{
		float temp1 = 1.0f / nt;
		cosine = -cosine;
		float root = 1.0f - (temp1*temp1)*(1.0f - cosine*cosine);

		transmission = in_dir*temp1 + normal*(temp1*cosine - sqrt(root));

		_extinction = rgb(1.0f, 1.0f, 1.0f);
	}
	else
	{
		float temp2 = (Dot(in_dir, normal));
		float root = 1.0f - (nt*nt)*(1.0f - temp2*temp2);

		if (root < 0.0f) return false;
		else transmission = in_dir*nt - normal*(nt*temp2 - sqrt(root));

		_extinction = extinction;
	}
	float temp3 = 1.0f - cosine;
	fresnel_scale = 1.0f - (R0 + (1.0f - R0)*temp3*temp3*temp3*temp3*temp3);
	return true;
}