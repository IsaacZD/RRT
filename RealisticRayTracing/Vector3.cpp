#include "Vector3.h"

std::istream& operator>>(std::istream &is, Vector3 &t)
{
	is >> t.x >> t.y >> t.z;
	return is;
}

std::ostream& operator<<(std::ostream &os, const Vector3 &t)
{
	os << '(' << t.x << ' ' << t.y << ' ' << t.z << ' ' << ')';
	return os;
}

float TripleProduct(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3)
{
	return Dot(Cross(v1, v2), v3);
}