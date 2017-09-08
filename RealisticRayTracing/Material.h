#pragma once

#include "Vector2.h"
#include "Shape.h"
#include "Ray.h"
#include "rgb.h"
#include "ONB.h"

class Material
{
public:
	virtual bool Emits() const { return false; }
	virtual rgb EmittedRadiance(const ONB &,		// ONB of hit point
		const Vector3 &,							// outgoing direction from light
		const Vector3 &,							// Texture point
		const Vector2 &)							// Texture coordinate
	{
		return rgb(0.f, 0.f, 0.f);
	}

	virtual rgb AmbientResponse(const ONB &,		// ONB of hit point
		const Vector3 &,							// incident direction
		const Vector3 &,							// Texture point
		const Vector2 &)							// Texture coordinate
	{
		return rgb(0.f, 0.f, 0.f);
	}

	virtual bool ExplicitBRDF(const ONB &,			// ONB of hit point
		const Vector3 &,							// outgoing vector v0
		const Vector3 &,							// outgoing vector v1
		const Vector3 &,							// Texture point
		const Vector2 &,							// Texture coordinate
		rgb &)
	{
		return false;
	}

	virtual bool DiffuseDirection(const ONB &,		// ONB of hit point
		const Vector3 &,							// incident vector
		const Vector3 &,							// Texture point
		const Vector2 &,							// Texture coordinate
		Vector2 &,									// random seed
		rgb &,										// value returned by Texture
		Vector3 &)
	{
		return false;
	}

	virtual bool SpecularDirection(const ONB &,		// ONB of hit point
		const Vector3 &,							// incident vector
		const Vector3 &,							// Texture point
		const Vector2 &,							// Texture coordinate
		Vector2 &,									// random seed
		rgb &,										// value returned by Texture
		Vector3 &)
	{
		return false;
	}

	virtual bool ScatterDirection(const Vector3 &,	// incident Vector
		const HitRecord &,							// hit we are shading
		Vector2 &,									// random seed
		rgb &,										// color to attenuate by
		bool &,										// count emitted light?
		float &,									// brdf scale
		Vector3 &)									// scattered direction
	{
		return false;
	}

	virtual bool TransmissionDirection(const ONB &,	// ONB of hit point
		const Vector3 &,							// incident unit vector
		const Vector3 &,							// Texture point
		const Vector2 &,							// Texture coordinate
		const Vector2 &,							// random seed
		rgb &,										// extinction color
		float &,									// fresnel scale
		Vector3 &)
	{
		return false;
	}

	virtual bool IsDiffuse() { return false; }
	virtual bool IsSpecular() { return false; }
	virtual bool IsTransmissive() { return false; }
	virtual int CausticPhotons() { return 0; }
	virtual int GlobalPhotons() { return 0; }
	virtual rgb PhotonColor() { return rgb(0.f, 0.f, 0.f); }
};
