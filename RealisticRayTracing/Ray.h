#pragma once
#ifndef _RAY_H_
#define _RAY_H_

#include "Vector3.h"
class Ray
{
public:
	Ray() { }
	Ray(const Vector3 &a, const Vector3 &b)
	{
		data[0] = a;
		data[1] = b;
	}
	Ray(const Ray& r) { *this = r; }
	Vector3 Origin() const { return o; }
	Vector3 Direction() const { return d; }
	Vector3 operator()(float t) const { return o + t*d; }
	Ray& operator=(const Ray &r) { o = r.o; d = r.d; return *this; }

public:
	union {
		struct { Vector3 o, d; };
		Vector3 data[2];
	};
};

inline std::ostream& operator<<(std::ostream &os, const Ray &r)
{
	os << '(' << r.o << ") + t(" << r.d << ')';
	return os;
}

#endif
