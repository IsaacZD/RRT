#pragma once
#ifndef _DYN_SPHERE_H_
#define _DYN_SPHERE_H_

#include "Shape.h"
#include "Vector3.h"
#include "Ray.h"
#include "rgb.h"
#include "Texture.h"

class DynSphere : public Shape
{
public:
	DynSphere(const Vector3 &ocenter, float radius, Texture *texture, float mintime, float maxtime);
	bool Hit(const Ray &r, float tmin, float tmax, float time, HitRecord &record) const;
	bool ShadowHit(const Ray &r, float tmin, float tmax, float time) const;
	Vector3 GetCenter(float time) const;


public:
	Vector3 ocenter;
	float mintime;
	float maxtime;
	float radius;
	Texture *texture;
};




#endif // !_DYN_SPHERE_H_

