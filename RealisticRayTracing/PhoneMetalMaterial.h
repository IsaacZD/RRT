#pragma once

#include "Material.h"

class Texture;

class PhongMetalMaterial : public Material
{
public:
	PhongMetalMaterial(Texture *rt, Texture *et) : R(rt), phong_exp(et) { }

	virtual rgb AmbientResponse(const ONB &,
		const Vector3 &incident,
		const Vector3 &tex_point,
		const Vector2 &uv) override;

	virtual bool SpecularDirection(const ONB &,
		const Vector3 &incident,
		const Vector3 &tex_point,
		const Vector2 &uv,
		Vector2 &seed,
		rgb &,
		Vector3 &) override;
	virtual bool IsSpecular() override { return true; }
public:
	Texture *R;
	Texture *phong_exp;
};