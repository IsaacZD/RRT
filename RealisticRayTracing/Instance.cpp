#include "Instance.h"
#include "ONB.h"

Instance::Instance(Matrix trans, Matrix trans_inverse, Shape *prim)
	: M(trans), N(trans_inverse), prim(prim)
{ }

Instance::Instance(Matrix trans, Shape *prim)
	: M(trans), N(trans), prim(prim)
{
	N.Invert();
}

bool Instance::Hit(const Ray &r, float tmin, float tmax, float time, HitRecord &rec) const
{
	Vector3 no = TransformLoc(N, r.o);
	Vector3 nd = TransformVec(N, r.d);
	Ray tray(no, nd);
	
	if (prim->Hit(tray, tmin, tmax, time, rec))
	{
		rec.pos = TransformLoc(M, rec.pos);
		//Vector3 normal = TransformVec(N.GetTranspose(), rec.uvw.w);
		//ONB uvw;
		//uvw.InitFromW(normal);
		//rec.uvw = uvw;
		return true;
	}
	else return false;
}

bool Instance::ShadowHit(const Ray &r, float tmin, float tmax, float time) const
{
	Vector3 no = TransformLoc(N, r.o);
	Vector3 nd = TransformVec(N, r.d);
	Ray tray(no, nd);

	return (prim->ShadowHit(tray, tmin, tmax, time));
}