#include "DynSphere.h"

DynSphere::DynSphere(const Vector3 &ocenter, float radius, Material *material, float mintime, float maxtime)
	: ocenter(ocenter), radius(radius), material(material), mintime(mintime), maxtime(maxtime)
{ }

bool DynSphere::Hit(const Ray &r, float tmin, float tmax, float time, HitRecord &record) const
{
	Vector3 new_center = GetCenter(time);
	Vector3 temp = r.Origin() - new_center;

	double a = Dot(r.d, r.d);
	double b = 2 * Dot(r.d, temp);
	double c = Dot(temp, temp) - radius*radius;

	double discriminant = b*b - 4 * a*c;

	if (discriminant > 0)
	{
		discriminant = sqrt(discriminant);
		double t = (-b - discriminant) / (2 * a);

		if (t < tmin)
			t = (-b + discriminant) / (2 * a);
		if (t<tmin || t>tmax)
			return false;

		record.t = t;
		record.pos = r.o + t*r.d;
		//record.normal = UnitVector(r.o + t*r.d - new_center);
		record.uvw.InitFromW(r.o - t*r.d - new_center);
		record.material = material;
		return true;
	}
	return false;
}

bool DynSphere::ShadowHit(const Ray &r, float tmin, float tmax, float time) const
{
	Vector3 new_center = GetCenter(time);
	Vector3 temp = r.o - new_center;

	double a = Dot(r.d, r.d);
	double b = 2 * Dot(r.d, temp);
	double c = Dot(temp, temp) - radius*radius;

	double discriminant = b*b - 4 * a*c;

	if (discriminant > 0)
	{
		discriminant = sqrt(discriminant);
		double t = (-b - discriminant) / (2 * a);

		if (t < tmin)
			t = (-b + discriminant) / (2 * a);
		if (t<tmin || t>tmax)
			return false;

		return true;
	}
	return false;
}

Vector3 DynSphere::GetCenter(float time) const
{
	float realtime = time * maxtime + (1.0f - time) * mintime;
	return Vector3(
		ocenter.x + realtime,
		ocenter.y + realtime,
		ocenter.z + realtime);
}

BBox DynSphere::BoundingBox(float time) const
{
	BBox bbox;
	Vector3 c = GetCenter(time);

	bbox.min.x = c.x - radius;
	bbox.min.y = c.y - radius;
	bbox.min.z = c.z - radius;

	bbox.max.x = c.x + radius;
	bbox.max.y = c.y + radius;
	bbox.max.z = c.z + radius;

	return bbox;
}