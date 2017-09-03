#pragma once

#include "Ray.h"
#include "Vector3.h"
#include "rgb.h"
#include "Material.h"
#include "BBox.h"
#include "ONB.h"

struct HitRecord
{
	float t;
	Vector3 pos;
	Vector3 tex_pos;
	ONB uvw;			// w is the outward normal
	Vector2 uv;
	Material *material;
};


class Shape
{
public:
	virtual bool Hit(const Ray &r, float tmin, float tmax, float time, HitRecord &record) const = 0;
	virtual bool ShadowHit(const Ray &r, float tmin, float tmax, float time) const = 0;
	virtual BBox BoundingBox(float time) const = 0;
};
