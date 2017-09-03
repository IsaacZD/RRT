#pragma once

#include "Shape.h"
#include "Vector2.h"
#include "Ray.h"
#include "Material.h"

class UVTriangle : public Shape
{
public:
	UVTriangle(const Vector3 &p0, const Vector3 &p1, const Vector3 &p2,
		const Vector2 &uv0, const Vector2 &uv1, const Vector2 &uv2, Material *material);
	bool Hit(const Ray &r, float tmin, float tmax, float time, HitRecord &record) const override;
	bool ShadowHit(const Ray &r, float tmin, float tmax, float time) const override;
	BBox BoundingBox(float time) const override { return bbox; }

public:
	Vector2 uv0, uv1, uv2;
	Vector3 p0, p1, p2;
	Material *material;
	BBox bbox;
};

