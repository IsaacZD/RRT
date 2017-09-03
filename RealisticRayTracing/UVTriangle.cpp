#include "UVTriangle.h"

UVTriangle::UVTriangle(const Vector3 &p0, const Vector3 &p1, const Vector3 &p2,
	const Vector2 &uv0, const Vector2 &uv1, const Vector2 &uv2, Material *material)
	: p0(p0), p1(p1), p2(p2), uv0(uv0), uv1(uv1), uv2(uv2), material(material)
{
	bbox.min.x = fmin(fmin(p0.x, p1.x), p2.x);
	bbox.min.y = fmin(fmin(p0.y, p1.y), p2.y);
	bbox.min.z = fmin(fmin(p0.z, p1.z), p2.z);

	bbox.max.x = fmax(fmax(p0.x, p1.x), p2.x);
	bbox.max.y = fmax(fmax(p0.y, p1.y), p2.y);
	bbox.max.z = fmax(fmax(p0.z, p1.z), p2.z);
}

bool UVTriangle::Hit(const Ray &r, float tmin, float tmax, float time, HitRecord &record) const
{
	float t;
	float A = p0.x - p1.x;
	float B = p0.y - p1.y;
	float C = p0.z - p1.z;

	float D = p0.x - p2.x;
	float E = p0.y - p2.y;
	float F = p0.z - p2.z;

	float G = r.d.x;
	float H = r.d.y;
	float I = r.d.z;

	float J = p0.x - r.o.x;
	float K = p0.y - r.o.y;
	float L = p0.z - r.o.z;

	float EIHF = E*I - H*F;
	float GFDI = G*F - D*I;
	float DHEG = D*H - E*G;

	float denom = (A*EIHF + B*GFDI + C*DHEG);
	float beta = (J*EIHF + K*GFDI + L*DHEG) / denom;
	if (beta <= 0.0f || beta >= 1.0f) return false;
	
	float AKJB = A*K - J*B;
	float JCAL = J*C - A*L;
	float BLKC = B*L - K*C;

	float gamma = (I*AKJB + H*JCAL + G*BLKC) / denom;
	if (gamma <= 0.0 || beta + gamma >= 1.0f) return false;

	t= -(F*AKJB + E*JCAL + D*BLKC) / denom;
	if (t>= tmin && t<= tmax)
	{
		record.t = t;
		record.pos = r.o + t*r.d;
		//record.normal = UnitVector(Cross((p1 - p0), (p2 - p0)));
		record.uvw.InitFromW(Cross(p1 - p0, p2 - p0));
		record.material = material;
		record.uv = (1 - beta - gamma)*uv0 + beta*uv1 + gamma*uv2;
		return true;
	}

	return false;
}



bool UVTriangle::ShadowHit(const Ray &r, float tmin, float tmax, float time) const
{
	float tval;
	float A = p0.x - p1.x;
	float B = p0.y - p1.y;
	float C = p0.z - p1.z;

	float D = p0.x - p2.x;
	float E = p0.y - p2.y;
	float F = p0.z - p2.z;

	float G = r.d.x;
	float H = r.d.y;
	float I = r.d.z;

	float J = p0.x - r.o.x;
	float K = p0.y - r.o.y;
	float L = p0.z - r.o.z;

	float EIHF = E*I - H*F;
	float GFDI = G*F - D*I;
	float DHEG = D*H - E*G;

	float denom = (A*EIHF + B*GFDI + C*DHEG);
	float beta = (J*EIHF + K*GFDI + L*DHEG) / denom;
	if (beta <= 0.0f || beta >= 1.0f) return false;

	float AKJB = A*K - J*B;
	float JCAL = J*C - A*L;
	float BLKC = B*L - K*C;

	float gamma = (I*AKJB + H*JCAL + G*BLKC) / denom;
	if (gamma <= 0.0f || beta + gamma >= 1.0f) return false;

	tval = -(F*AKJB + E*JCAL + D*BLKC) / denom;

	return (tval >= tmin&&tval <= tmax);
}
