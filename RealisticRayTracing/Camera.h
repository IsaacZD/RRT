#pragma once

#include "Ray.h"
#include "ONB.h"

class Camera
{
public:
	Camera(const Camera &orig) :
		center(orig.center), corner(orig.corner), across(orig.across),
		uvw(orig.uvw), lens_radius(orig.lens_radius), u0(orig.u0), u1(orig.u1),
		v0(orig.v0), v1(orig.v1), d(orig.d) { }

	Camera(const Vector3 &c, const Vector3 &gaze, const Vector3 &vup, float aperture, float left,
		float right, float bottom, float top, float distance) :
		center(c), d(distance), u0(left), u1(right), v0(bottom), v1(top)
	{
		lens_radius = aperture/2.0f;
		uvw.InitFromWV(-gaze, vup);
		corner = center + u0*uvw.u + v0*uvw.v - d*uvw.w;
		across = (u1 - u0)*uvw.u;
		up = (v1 - v0)*uvw.v;
	}

	Ray GetRay(float a, float b, float xi1, float xi2) const // a,b是像素坐标，xi1,xi2是棱镜上的坐标 [0,1]
	{
		Vector3 origin = center + 2.0f*(xi1 - 0.5f)*lens_radius*uvw.u + 2.0f*(xi2 - 0.5f)*lens_radius*uvw.v;
		Vector3 target = corner + across*a + up*b;

		return Ray(origin, UnitVector(target - origin));
	}


public:
	Vector3 center, corner, across, up; // corner左下角顶点 across向右的边向量
	ONB uvw;
	float lens_radius;
	int u0, u1, v0, v1;
	float d;
};

