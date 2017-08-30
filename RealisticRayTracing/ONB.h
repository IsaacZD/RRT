#pragma once

#include "Vector3.h"
#include <iostream>


class ONB
{
public:
	ONB() {};
	ONB(const Vector3 &u, const Vector3 &v, const Vector3 &w) : u(u), v(v), w(w) { }
	
	void InitFromU(const Vector3 &u);
	void InitFromV(const Vector3 &v);
	void InitFromW(const Vector3 &w);

	void Set(const Vector3 &u, const Vector3 &v, const Vector3 &w) { this->v = v; this->u = u; this->w = w; }
	void InitFromUV(const Vector3 &u, const Vector3 &v);
	void InitFromVU(const Vector3 &v, const Vector3 &u);

	void InitFromUW(const Vector3 &u, const Vector3 &w);
	void InitFromWU(const Vector3 &w, const Vector3 &u);

	void InitFromVW(const Vector3 &v, const Vector3 &w);
	void InitFromWV(const Vector3 &w, const Vector3 &v);

public:
	Vector3 u, v, w;
};

std::istream& operator>>(std::istream &is, ONB &t);
std::ostream& operator<<(std::ostream &os, const ONB &t);
bool operator==(const ONB &o1, const ONB &o2);