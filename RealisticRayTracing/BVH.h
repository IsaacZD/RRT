#pragma once

#include "Shape.h"
#include "BBox.h"

class BVH : public Shape
{
public:
	BVH() { }
	BVH(Shape **surfaces, int num_surfaces);
	BVH(Shape *left, Shape *right) : left(left), right(right)
	{
		bbox = Surround(left->BoundingBox(0.f), right->BoundingBox(0.f));
	}
	BVH(Shape *left, Shape *right, const BBox &bbox) : bbox(bbox), left(left), right(right) { }
	bool Hit(const Ray &r, float tmin, float tmax, float time, HitRecord &rec) const override;
	bool ShadowHit(const Ray &r, float tmin, float tmax, float time) const override;
	BBox BoundingBox(float time) const override { return bbox; }
	Shape* BuildBranch(Shape **surfaces, int num_surfaces, int axis = 0);

public:
	BBox bbox;
	Shape *left, *right;
};

