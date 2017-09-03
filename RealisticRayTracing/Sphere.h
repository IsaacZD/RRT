#pragma once

#include "Shape.h"
#include "Vector3.h"
#include "Ray.h"
#include "rgb.h"
#include "Material.h"

class Sphere : public Shape
{
public:
	Sphere(const Vector3 &center, float radius, Material *material);
	bool Hit(const Ray &r, float tmin, float tmax, float time, HitRecord &record) const override;
	bool ShadowHit(const Ray &r, float tmin, float tmax, float time) const override;
	BBox BoundingBox(float time) const override { return bbox; }
public:
	Vector3 center;
	float radius;
	Material *material;
	BBox bbox;
};
