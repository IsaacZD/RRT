#include "Sphere.h"

Sphere::Sphere(const Vector3 &center, float radius, Material *material)
	:center(center), radius(radius), material(material)
{
	bbox.min.x = center.x - radius;
	bbox.min.y = center.y - radius;
	bbox.min.z = center.z - radius;

	bbox.max.x = center.x + radius;
	bbox.max.y = center.y + radius;
	bbox.max.z = center.z + radius;
}

bool Sphere::Hit(const Ray &r, float tmin, float tmax, float time, HitRecord &record) const
{
	Vector3 temp = r.o - center;

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
		//record.normal = UnitVector(r.o + t*r.d - center);
		record.uvw.InitFromW(r.o + t*r.d - center);
		record.material = material;
		return true;
	}
	return false;
}

bool Sphere::ShadowHit(const Ray &r, float tmin, float tmax, float time) const
{
	Vector3 temp = r.o - center;
	
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