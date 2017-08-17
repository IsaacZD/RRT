#include "ONB.h"

#define ONB_EPSILON 0.01f

void ONB::InitFromU(const Vector3 &u)
{
	Vector3 n(1.0f, 0.0f, 0.0f);
	Vector3 m(0.0f, 1.0f, 0.0f);

	this->u = UnitVector(u);
	this->v = Cross(this->u, n);
	if (this->v.Length() < ONB_EPSILON)
		this->v = Cross(this->u, m);
	this->w = Cross(this->u, this->v);
}

void ONB::InitFromV(const Vector3 &v)
{
	Vector3 n(1.0f, 0.0f, 0.0f);
	Vector3 m(0.0f, 1.0f, 0.0f);

	this->v = UnitVector(v);
	this->u = Cross(this->v, n);
	if (this->u.SquaredLength() < ONB_EPSILON)
		this->u = Cross(this->v, m);
	this->w = Cross(this->u, this->v);
}

void ONB::InitFromW(const Vector3 &w)
{
	Vector3 n(1.0f, 0.0f, 0.0f);
	Vector3 m(0.0f, 1.0f, 0.0f);

	this->w = UnitVector(w);
	this->u = Cross(this->w, n);
	if (this->u.Length() < ONB_EPSILON)
		this->u = Cross(this->w, m);
	this->v = Cross(this->w, this->u);
}

void ONB::InitFromUV(const Vector3 &u, const Vector3 &v)
{
	this->u = UnitVector(u);
	this->w = UnitVector(Cross(u, v));
	this->v = Cross(this->w, this->u);
}

void ONB::InitFromVU(const Vector3 &v, const Vector3 &u)
{
	this->v = UnitVector(v);
	this->w = UnitVector(Cross(u, v));
	this->u = Cross(this->v, this->w);
}

void ONB::InitFromUW(const Vector3 &u, const Vector3 &w)
{
	this->u = UnitVector(u);
	this->v = UnitVector(Cross(w, u));
	this->w = Cross(this->u, this->v);
}

void ONB::InitFromWU(const Vector3 &w, const Vector3 &u)
{
	this->w = UnitVector(w);
	this->v = UnitVector(Cross(w, u));
	this->u = Cross(this->v, this->w);
}

void ONB::InitFromVW(const Vector3 &v, const Vector3 &w)
{
	this->v = UnitVector(v);
	this->u = UnitVector(Cross(v, w));
	this->w = Cross(this->u, this->v);
}

void ONB::InitFromWV(const Vector3 &w, const Vector3 &v)
{
	this->w = UnitVector(w);
	this->u = UnitVector(Cross(v, w));
	this->v = Cross(this->w, this->u);
}

bool operator==(const ONB &o1, const ONB &o2)
{
	return (o1.u == o2.u && o1.v == o2.v && o1.w == o2.w);
}

std::istream& operator>>(std::istream &is, ONB &t)
{
	Vector3 new_u, new_v, new_w;
	is >> new_u >> new_v >> new_w;
	t.InitFromUV(new_u, new_v);
	return is;
}

std::ostream& operator<<(std::ostream &os, const ONB &t)
{
	os << t.u << '\n' << t.v << '\n' << t.w << '\n';
	return os;
}