#pragma once

#include <iostream>

class rgb
{
public:
	rgb() : r(0.f), g(0.f), b(0.f) { }
	rgb(float intensity) : r(intensity), g(intensity), b(intensity) { }
	rgb(float r, float g, float b) : r(r), g(g), b(b) { }
	rgb(const rgb &original) : r(original.r), g(original.g), b(original.b) { }

	void SetRed(float red) { r = red; }
	void SetGreen(float green) { g = green; }
	void SetBlue(float blue) { b = blue; }

	rgb& operator=(const rgb &rhs);
	rgb& operator+=(const rgb &rhs);
	rgb& operator*=(const rgb &rhs);
	rgb& operator/=(const rgb &rhs);
	rgb& operator*=(float rhs);
	rgb& operator/=(float rhs);

	rgb operator+() const { return *this; }
	rgb operator-() const { return rgb(-r, -g, -b); }

	float R() const { return r; }
	float G() const { return g; }
	float B() const { return b; }

	void Clamp();

	friend std::ostream& operator<<(std::ostream &out, const rgb &the_rgb);
public:
	float r, g, b;
};

inline rgb operator*(const rgb &c, float f)
{
	return rgb(c.r*f, c.g*f, c.b*f);
}

inline rgb operator*(float f, const rgb &c)
{
	return rgb(c.r*f, c.g*f, c.b*f);
}

inline rgb operator/(const rgb &c, float f)
{
	return rgb(c.r / f, c.g / f, c.b / f);
}

inline rgb operator*(const rgb &c1, const rgb &c2)
{
	return rgb(c1.r*c2.r, c1.g*c2.g, c1.b*c2.b);
}

inline rgb operator/(const rgb &c1, const rgb &c2)
{
	return rgb(c1.r / c2.r, c1.g / c2.g, c1.b / c2.b);
}

inline rgb operator+(const rgb &c1, const rgb &c2)
{
	return rgb(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b);
}

inline rgb& rgb::operator+=(const rgb &rhs)
{
	*this = *this + rhs;
	return *this;
}

inline rgb& rgb::operator*=(float rhs)
{
	*this = *this * rhs;
	return *this;
}

inline rgb& rgb::operator/=(float rhs)
{
	*this = *this / rhs;
	return *this;
}

inline rgb& rgb::operator*=(const rgb &rhs)
{
	*this = *this * rhs;
	return *this;
}

inline rgb& rgb::operator/=(const rgb &rhs)
{
	*this = *this / rhs;
	return *this;
}

inline rgb& rgb::operator=(const rgb &rhs)
{
	r = rhs.r;
	g = rhs.g;
	b = rhs.b;
	return *this;
}

inline void rgb::Clamp()
{
	if (r > 1.0f) r = 1.0f;
	if (g > 1.0f) g = 1.0f;
	if (b > 1.0f) b = 1.0f;

	if (r < 0.0f) r = 0.0f;
	if (g < 0.0f) g = 0.0f;
	if (b < 0.0f) b = 0.0f;
}

inline std::ostream& operator<<(std::ostream &out, const rgb &the_rgb)
{
	out << the_rgb.r << ' ' << the_rgb.g << ' ' << the_rgb.b;
	return out;
}
