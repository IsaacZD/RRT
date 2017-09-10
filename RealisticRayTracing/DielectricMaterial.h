#pragma once
#include "Material.h"
#include "rgb.h"
#include "Vector3.h"

class Texture;

class DielectricMaterial : public Material
{
public:
	DielectricMaterial() { }
	DielectricMaterial(float nt, const rgb & ex);

	virtual bool SpecularDirection(const ONB &uvw,
		const Vector3 &in_dir,
		const Vector3 &tex_pos,
		const Vector2 &uv,
		Vector2 &rseed,
		rgb &ratio,
		Vector3 &reflection) override;

	virtual bool TransmissionDirection(const ONB &uvw,
		const Vector3 &in_dir,
		const Vector3 &tex_pos,
		const Vector2 &uv,
		const Vector2 &rseed,
		rgb &_extinction,
		float &fresnel_scale,
		Vector3 &transmission) override;
	virtual bool IsTransmissive() override { return true; }

public:
	float R0;
	float nt;
	rgb extinction;
};
