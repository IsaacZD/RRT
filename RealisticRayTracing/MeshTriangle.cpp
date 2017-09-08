#include "Mesh.h"
#include "MeshTriangle.h"

MeshTriangleUV::MeshTriangleUV(Mesh *mesh, int p0, int p1, int p2, int index)
	: mesh_ptr(mesh)
{
	p[0] = p0; p[1] = p1; p[2] = p2;
	Vector3 &pp0 = mesh_ptr->vertUVs[p0].vertex;
	Vector3 &pp1 = mesh_ptr->vertUVs[p1].vertex;
	Vector3 &pp2 = mesh_ptr->vertUVs[p2].vertex;

	bbox.min.x = fmin(fmin(pp0.x, pp1.x), pp2.x);
	bbox.min.y = fmin(fmin(pp0.y, pp1.y), pp2.y);
	bbox.min.z = fmin(fmin(pp0.z, pp1.z), pp2.z);

	bbox.max.x = fmax(fmax(pp0.x, pp1.x), pp2.x);
	bbox.max.y = fmax(fmax(pp0.y, pp1.y), pp2.y);
	bbox.max.z = fmax(fmax(pp0.z, pp1.z), pp2.z);
}

MeshTriangleUV::~MeshTriangleUV()
{ }

bool MeshTriangleUV::Hit(const Ray &r, float tmin, float tmax, float time, HitRecord &rec) const
{
	Vector3 p0((mesh_ptr->vertUVs[p[0]]).vertex);
	Vector3 p1((mesh_ptr->vertUVs[p[1]]).vertex);
	Vector3 p2((mesh_ptr->vertUVs[p[2]]).vertex);

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
		double alpha = 1.0 - beta - gamma;
		Vector2 u0(mesh_ptr->vertUVs[p[0]].uv);
		Vector2 u1(mesh_ptr->vertUVs[p[1]].uv);
		Vector2 u2(mesh_ptr->vertUVs[p[2]].uv);
		rec.pos = r.o + t*r.d;
		rec.uv = Vector2(alpha*u0.x + beta*u1.x + gamma*u2.x, alpha*u0.y + beta*u1.y + gamma*u2.y);
		rec.material = mesh_ptr->GetMaterial();
		rec.t = t;
		//rec.normal = UnitVector(Cross(p1 - p0, p2 - p0));
		rec.uvw.InitFromW(Cross(p1 - p0, p2 - p0));

		return true;
	}
	return false;	
}

bool MeshTriangleUV::ShadowHit(const Ray &r, float tmin, float tmax, float time) const
{
	Vector3 p0((mesh_ptr->vertUVs[p[0]]).vertex);
	Vector3 p1((mesh_ptr->vertUVs[p[1]]).vertex);
	Vector3 p2((mesh_ptr->vertUVs[p[2]]).vertex);

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