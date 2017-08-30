#pragma once

#include "Shape.h"
#include "Matrix.h"

class Instance : public Shape
{
public:
	Instance() { }
	~Instance() { }
	Instance(Matrix trans, Matrix trans_inverse, Shape *prim);
	Instance(Matrix trans, Shape *prim);
	bool Hit(const Ray &r, float tmin, float tmax, float time, HitRecord &rec) const override;
	bool ShadowHit(const Ray &r, float tmin, float tmax, float time) const override;
	BBox BoundingBox(float time) const override { return prim->BoundingBox(time); }

public:
	Matrix M;
	Matrix N; // N = M.Inverte()
	Shape *prim;
};