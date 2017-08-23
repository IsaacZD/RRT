#include "UVSphere.h"

UVSphere::UVSphere(const Vector3 &center, float radius, Texture *tex)
	:center(center), radius(radius), tex(tex) 
{ }

bool UVSphere::Hit(const Ray &r, float tmin, float tmax, float time, HitRecord &rec) const
{
	Vector3 temp = r.o - center;
	double a = Dot(r.d, r.d);
	double b = 2 * Dot(r.d, temp);
	double c = Dot(temp, temp) - radius*radius;

	double discriminant = b*b - 4.0*a*c;

	if (discriminant > 0.0)
	{
		discriminant = sqrt(discriminant);
		double t = (-b - discriminant) / (2.0*a);

		if (t < tmin)
			t = (-b + discriminant) / (2.0*a);
		if (t<tmin || t>tmax)
			return false;

		rec.t = t;
		rec.pos = r.o + t*r.d;
		Vector3 n = rec.normal = (rec.pos - center) / radius;
		
		float twopi = 6.28318530718f;
		float pi = 3.1415926535f;
		float theta = acos(n.z);
		float phi = atan2(n.y, n.x);
		if (phi < 0.0f) phi += twopi;

		float one_over_2pi = .159154943092f;
		float one_over_pi = .318309886184f;
		rec.uv = Vector2(phi*one_over_2pi, (pi - theta)*one_over_pi);

		rec.texture = tex;
		return true;
	}
	return false;
}

bool UVSphere::ShadowHit(const Ray &r, float tmin, float tmax, float time) const
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

