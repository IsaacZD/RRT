#pragma once

#include<cmath>
#include<iostream>

class Vector3
{
public:
	Vector3() {}
	Vector3(float e0, float e1, float e2);
	Vector3(const Vector3 &v) { *this = v; }

	const Vector3& operator+() const;
	Vector3 operator-() const;

	float Length() const;
	float SquaredLength() const;

	void MakeUnitVector();

	void SetX(float x) { this->x = x; }
	void SetY(float y) { this->y = y; }
	void SetZ(float z) { this->z = z; }

	float MinComponent() const;
	float MaxComponent() const;
	float MinAbsComponent() const;
	float MaxAbsComponent() const;
	int IndexOfMinAbsComponent() const;
	int IndexOfMaxAbsComponent() const;
	int IndexOfMaxComponent() const;
	int IndexOfMinComponent() const;

	Vector3& operator=(const Vector3 &v2);
	Vector3& operator+=(const Vector3 &v2);
	Vector3& operator-=(const Vector3 &v2);
	Vector3& operator*=(const float t);
	Vector3& operator/=(const float t);

public:
	union {
		struct { float x, y, z; };
		float e[3];
	};
};

inline Vector3::Vector3(float e0, float e1, float e2)
{
	x = e0; y = e1; z = e2;
}

inline const Vector3& Vector3::operator+() const
{
	return *this;
}

inline Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

inline float Vector3::Length() const
{
	return sqrt(x*x + y*y + z*z);
}

inline float Vector3::SquaredLength() const
{
	return x*x + y*y + z*z;
}

inline void Vector3::MakeUnitVector()
{
	*this /= Length();
}

inline float Vector3::MinComponent() const
{
	float temp = x;
	if (y < temp) temp = y;
	if (z < temp) temp = z;
	return temp;
}

inline float Vector3::MaxComponent() const
{
	float temp = x;
	if (y > temp) temp = y;
	if (z > temp) temp = z;

	return temp;
}

inline float Vector3::MaxAbsComponent() const
{
	float temp = fabs(x);
	if (fabs(y) > temp) temp = fabs(y);
	if (fabs(z) > temp) temp = fabs(z);

	return temp;
}

inline float Vector3::MinAbsComponent() const
{
	float temp = fabs(x);
	if (fabs(y) < temp) temp = fabs(y);
	if (fabs(z) < temp) temp = fabs(z);

	return temp;
}

inline int Vector3::IndexOfMinComponent() const
{
	int index = 0;
	float temp = x;

	if (y < temp) { temp = y; index = 1; }
	if (z < temp) index = 2;

	return index;
}

inline int Vector3::IndexOfMinAbsComponent() const
{
	int index = 0;
	float temp = fabs(x);
	if (fabs(y) < temp) { temp = fabs(y); index = 1; }
	if (fabs(z) < temp)index = 2;

	return index;
}

inline bool operator==(const Vector3 &v1, const Vector3 &v2)
{
	if (v1.x != v2.x) return false;
	if (v1.y != v2.y) return false;
	if (v1.z != v2.z) return false;
	return true;
}

inline bool operator!=(const Vector3 &v1, const Vector3 &v2)
{
	return !(v1 == v2);
}

inline int Vector3::IndexOfMaxComponent() const
{
	int index = 0;
	float temp = x;

	if (y > temp) { temp = y; index = 1; }
	if (z > temp) index = 2;

	return index;
}

inline int Vector3::IndexOfMaxAbsComponent() const
{
	int index = 0;
	float temp = fabs(x);
	if (fabs(y) > temp) { temp = fabs(y); index = 1; }
	if (fabs(z) > temp) index = 2;

	return index;
}

inline Vector3 operator*(float scalar, const Vector3 &vec)
{
	return Vector3(vec.x*scalar, vec.y*scalar, vec.z*scalar);
}
inline Vector3 operator*(const Vector3 &vec, float scalar)
{
	return scalar*vec;
}

inline Vector3 operator/(const Vector3 &vec, float scalar)
{
	return Vector3(vec.x / scalar, vec.y / scalar, vec.z / scalar);
}

inline Vector3 operator+(const Vector3 &v1, const Vector3 &v2)
{
	return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

inline Vector3 operator-(const Vector3 &v1, const Vector3 &v2)
{
	return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

inline Vector3& Vector3::operator+=(const Vector3 &v2)
{
	*this = *this + v2;
	return *this;
}

inline Vector3& Vector3::operator-=(const Vector3 &v2)
{
	*this = *this - v2;
	return *this;
}

inline Vector3& Vector3::operator=(const Vector3 &v2)
{
	x = v2.x; y = v2.y; z = v2.z;
	return *this;
}

inline Vector3& Vector3::operator*=(float t)
{
	*this = *this*t;
	return *this;
}

inline Vector3& Vector3::operator/=(float t)
{
	*this = *this / t;
	return *this;
}

inline float Dot(const Vector3 &v1, const Vector3 &v2)
{
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

inline Vector3 Cross(const Vector3 &v1, const Vector3 &v2)
{
	Vector3 temp;

	temp.x = v1.y*v2.z - v1.z*v2.y;
	temp.y = v1.z*v2.x - v1.x*v2.z;
	temp.z = v1.x*v2.y - v1.y*v2.x;
	
	return temp;
}

inline Vector3 MinVec(const Vector3 &v1, const Vector3 & v2)
{
	Vector3 vec(v1);
	if (v2.x < v1.x) vec.x = v2.x;
	if (v2.y < v1.y) vec.y = v2.y;
	if (v2.z < v1.z) vec.z = v2.z;

	return vec;
}

inline Vector3 MaxVec(const Vector3 &v1, Vector3 &v2)
{
	Vector3 vec(v1);
	if (v2.x > v1.x) vec.x = v2.x;
	if (v2.y > v1.y) vec.y = v2.y;
	if (v2.z > v1.z) vec.z = v2.z;

	return vec;
}

inline Vector3 UnitVector(const Vector3 &vec)
{
	return (vec / vec.Length());
}

std::istream& operator>>(std::istream &is, Vector3 &t);

std::ostream& operator<<(std::ostream &os, const Vector3 &t);