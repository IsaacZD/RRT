#pragma once
#ifndef _UV_SPHERE_H_
#define _UV_SPHERE_H_

#include "Shape.h"
#include "Vector3.h"
#include "Ray.h"
#include "Texture.h"

class UVSphere : public Shape
{
public:
	UVSphere(const Vector3 &center, float radius, Texture *tex);
	bool Hit(const Ray &r, float tmin, float tmax, float time, HitRecord &record) const;
	bool ShadowHit(const Ray &r, float tmin, float tmax, float time) const;

public:
	Vector3 center;
	float radius;
	Texture *tex;
};

#endif // !_UV_SPHERE_H_

