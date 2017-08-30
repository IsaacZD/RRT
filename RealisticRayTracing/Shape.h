#pragma once

#include "Ray.h"
#include "Vector3.h"
#include "rgb.h"
#include "Texture.h"
#include "BBox.h"

struct HitRecord
{
	float t;
	Vector3 normal;
	Vector2 uv;
	Vector3 pos;
	Texture *texture;
	//ONB uvw;
};

class Shape
{
public:
	virtual bool Hit(const Ray &r, float tmin, float tmax, float time, HitRecord &record) const = 0;
	virtual bool ShadowHit(const Ray &r, float tmin, float tmax, float time) const = 0;
	virtual BBox BoundingBox(float time) const = 0;
};
