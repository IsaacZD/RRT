#pragma once

#include "Vertex.h"
#include "Shape.h"
#include "Texture.h"

class Mesh
{
public:
	Mesh() { }
	~Mesh() { }
	Texture* GetTexture() const { return tex; }
public:
	Texture *tex;
	Vector3 *verts;
	VertexUV *vertUVs;
	VertexN *vertNs;
	VertexUVN *vertUVNs;
};
