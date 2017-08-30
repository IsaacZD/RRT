#pragma once

#include "Vector3.h"
class Ray
{
public:
	Ray() { }
	Ray(const Vector3 &a, const Vector3 &b)
	{
		SetOrigin(a);
		SetDirection(b);
	}
	Ray(const Ray& r) { *this = r; }
	Vector3 Origin() const { return o; }
	Vector3 Direction() const { return d; }

	void SetOrigin(const Vector3 &v) { o = v; }
	void SetDirection(const Vector3 &v)
	{
		d = v;
		extra = Vector3(1.0f / v.x, 1.f / v.y, 1.f / v.z);

		posneg[0] = (d.x > 0 ? 0 : 1);
		posneg[1] = (d.y > 0 ? 0 : 1);
		posneg[2] = (d.z > 0 ? 0 : 1);
	}

	Vector3 operator()(float t) const { return o + t*d; }
	Ray& operator=(const Ray &r) { SetOrigin(r.o); SetDirection(r.d); return *this; }

public:
	union {
		struct { Vector3 o, d, extra; };
		Vector3 data[3];
	};
	int posneg[3];
};

inline std::ostream& operator<<(std::ostream &os, const Ray &r)
{
	os << '(' << r.o << ") + t(" << r.d << ')';
	return os;
}
