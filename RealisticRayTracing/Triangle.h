#pragma once

#include "Shape.h"
#include "Vector3.h"
#include "rgb.h"
#include "Ray.h"
#include "Material.h"

class Triangle : public Shape
{
public:
	Triangle(const Vector3 &p0, const Vector3 &p1, const Vector3 &p2, Material *material);
	bool Hit(const Ray &r, float tmin, float tmax, float time, HitRecord &record) const override;
	bool ShadowHit(const Ray &r, float tmin, float tmax, float time) const override;
	BBox BoundingBox(float time) const override { return bbox; }
public:
	Vector3 p0, p1, p2;
	Material *material;
	BBox bbox;
};
