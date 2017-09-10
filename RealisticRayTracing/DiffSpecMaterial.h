#pragma once
#include "Material.h"
#include "RNG.h"
#include "Shape.h"

class DiffSpecMaterial : public Material
{
public:
	DiffSpecMaterial() { }
	DiffSpecMaterial(Material *d, Material *s, float r0 = .05f) : diff_mat(d), spec_mat(s), R0(r0) { }

	virtual rgb AmbientResponse(const ONB &uvw,
		const Vector3 &incident,
		const Vector3 &tex_point,
		const Vector2 &uv) override;

	virtual bool ExplicitBRDF(const ONB &uvw,
		const Vector3 &v0,
		const Vector3 &v1,
		const Vector3 &tex_point,
		const Vector2 &uv,
		rgb &color) override;

	virtual bool ScatterDirection(const Vector3 &incident,
		const HitRecord &record,
		Vector2 &seed,
		rgb &color,
		bool &emit,
		float &scale,
		Vector3 &direction) override;
	virtual bool IsDiffuse() override { return true; }
	virtual bool IsSpecular() override { return true; }

public:
	float R0;
	RNG rng;
	Material *diff_mat;
	Material *spec_mat;
};