#pragma once

#include "Ray.h"

class BBox
{
public:
	BBox() { }
	BBox(const Vector3 &a, const Vector3 &b) : min(a), max(b) { }
	BBox(const BBox &box) : min(box.min), max(box.max) { }
	bool RayIntersect(const Ray &r, float tmin, float tmax) const;

	BBox& operator=(const BBox &b)
	{
		min = b.min; max = b.max;
	}

public:
	union {
		struct { Vector3 min, max; };
		Vector3 pp[2];
	};
};

inline BBox Surround(const BBox &b1, const BBox &b2)
{
	return BBox(
		Vector3(
			b1.min.x < b2.min.x ? b1.min.x : b2.min.x,
			b1.min.y < b2.min.y ? b1.min.y : b2.min.y,
			b1.min.z < b2.min.z ? b1.min.z : b2.min.z),
		Vector3(
			b1.max.x > b2.max.x ? b1.max.x : b2.max.x,
			b1.max.y > b2.max.y ? b1.max.y : b2.max.y,
			b1.max.z > b2.max.z ? b1.max.z : b2.max.z));
}

inline bool BBox::RayIntersect(const Ray &r, float tmin, float tmax) const
{
	float interval_min = tmin;
	float interval_max = tmax;

	int posneg = r.posneg[0];
	float t0 = (pp[posneg].x - r.o.x)*r.extra.x;
	float t1 = (pp[1 - posneg].x - r.o.x)*r.extra.x;
	if (t0 > interval_min) interval_min = t0;
	if (t1 < interval_max) interval_max = t1;
	if (interval_min > interval_max) return false;

	posneg = r.posneg[1];
	t0 = (pp[posneg].y - r.o.y)*r.extra.y;
	t1 = (pp[1 - posneg].y - r.o.y)*r.extra.y;
	if (t0 > interval_min) interval_min = t0;
	if (t1 < interval_max) interval_max = t1;
	if (interval_min > interval_max) return false;

	posneg = r.posneg[2];
	t0 = (pp[posneg].z - r.o.z)*r.extra.z;
	t1 = (pp[1 - posneg].z - r.o.z)*r.extra.z;
	if (t0 > interval_min) interval_min = t0;
	if (t1 < interval_max) interval_max = t1;
	return (interval_min <= interval_max);
}