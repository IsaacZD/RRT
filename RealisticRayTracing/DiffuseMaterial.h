#pragma once

#include "Material.h"

class Texture;

class DiffuseMaterial : public Material
{
public:
	DiffuseMaterial(Texture *t) : R(t) { }
	virtual rgb AmbientResponse(const ONB &, const Vector3 &in_direction, const Vector3 &tex_point, const Vector2 &uv) override;
	virtual bool ExplicitBRDF(const ONB &, const Vector3 &v1, const Vector3 &v2, const Vector3 &tex_point, const Vector2 &uv, rgb &) override;
	virtual bool DiffuseDirection(const ONB &, const Vector3 &incident, const Vector3 &tex_point, const Vector2 &uv, Vector2 &seed, rgb &, Vector3 &) override;
public:
	Texture *R;
};