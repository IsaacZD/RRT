#pragma once

#include "Shape.h"

class Mesh;
class Texture;

class MeshTriangleUV : public Shape
{
public:
	MeshTriangleUV(Mesh *mesh, int p0, int p1, int p2, int index);
	~MeshTriangleUV();
	bool Hit(const Ray &r, float tmin, float tmax, float time, HitRecord &rec) const override;
	bool ShadowHit(const Ray &r, float tmin, float tmax, float time) const override;
	BBox BoundingBox(float time) const override { return bbox; }
public:
	int p[3];
	Mesh *mesh_ptr;
	BBox bbox;
};


