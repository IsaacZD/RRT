#pragma once

#include "Vertex.h"
#include "Shape.h"
#include "Material.h"

class Mesh
{
public:
	Mesh() { }
	~Mesh() { }
	Material* GetMaterial() const { return material; }
public:
	Material *material;
	Vector3 *verts;
	VertexUV *vertUVs;
	VertexN *vertNs;
	VertexUVN *vertUVNs;
};
