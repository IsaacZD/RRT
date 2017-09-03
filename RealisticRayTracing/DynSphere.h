#pragma once

#include "Shape.h"
#include "Vector3.h"
#include "Ray.h"
#include "rgb.h"
#include "Material.h"

class DynSphere : public Shape
{
public:
	DynSphere(const Vector3 &ocenter, float radius, Material *material, float mintime, float maxtime);
	bool Hit(const Ray &r, float tmin, float tmax, float time, HitRecord &record) const;
	bool ShadowHit(const Ray &r, float tmin, float tmax, float time) const;
	Vector3 GetCenter(float time) const;
	BBox BoundingBox(float time) const override;
public:
	Vector3 ocenter;
	float mintime;
	float maxtime;
	float radius;
	Material *material;
};
