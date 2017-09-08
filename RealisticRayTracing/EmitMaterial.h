#pragma once
#include "Material.h"

class EmitMaterial : public Material
{
public:
	EmitMaterial() : color(1.f, 1.f, 1.f) { }
	EmitMaterial(rgb c) : color(c) { }
	virtual rgb EmittedRadiance(const ONB &,
		const Vector3 &,
		const Vector3 &,
		const Vector2 &) override
	{
		return color;
	}

public:
	rgb color;
};
