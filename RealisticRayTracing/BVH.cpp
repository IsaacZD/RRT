#include "BVH.h"
#include "qsplit.h"

BVH::BVH(Shape **shapes, int num_shapes)
{
	if (num_shapes == 1) new(this) BVH(shapes[0], shapes[0]);
	else if (num_shapes == 2) new(this) BVH(shapes[0], shapes[1]);
	else
	{
		bbox = shapes[0]->BoundingBox(0.f);
		for (int i = 1; i < num_shapes; i++)
			bbox = Surround(bbox, shapes[i]->BoundingBox(0.f));
		Vector3 pivot = (bbox.max + bbox.min) / 2.f;

		int mid_point = QSplit(shapes, num_shapes, pivot.x, 0);

		left = BuildBranch(shapes, mid_point, 1);
		right = BuildBranch(&shapes[mid_point], num_shapes - mid_point, 1);
	}

}

bool BVH::Hit(const Ray &r, float tmin, float tmax, float time, HitRecord &rec) const
{
	if (!(bbox.RayIntersect(r, tmin, tmax))) return false;

	bool isahit1 = false;
	bool isahit2 = false;
	rec.t = tmax;

	isahit1 = left->Hit(r, tmin, tmax, time, rec);
	isahit2 = right->Hit(r, tmin, rec.t, time, rec);

	return (isahit1 || isahit2);
}

bool BVH::ShadowHit(const Ray &r, float tmin, float tmax, float time) const
{
	if (!(bbox.RayIntersect(r, tmin, tmax))) return false;

	if (right->ShadowHit(r, tmin, tmax, time)) return true;
	return left->ShadowHit(r, tmin, tmax, time);
}

Shape* BVH::BuildBranch(Shape **shapes, int shape_size, int axis)
{
	if (shape_size == 1) return shapes[0];
	if (shape_size == 2) return new BVH(shapes[0], shapes[1]);

	BBox box = shapes[0]->BoundingBox(0.f);
	for (int i = 1; i < shape_size; i++)
		box = Surround(box, shapes[i]->BoundingBox(0.f));

	Vector3 pivot = (box.max + box.min) / 2.f;

	int mid_point = QSplit(shapes, shape_size, pivot[axis], axis);

	Shape *left = BuildBranch(shapes, mid_point, (axis + 1) % 3);
	Shape *right = BuildBranch(&shapes[mid_point], shape_size - mid_point, (axis + 1) % 3);
	return new BVH(left, right, box);
}