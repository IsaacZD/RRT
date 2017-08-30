#pragma once

#include "Texture.h"
#include "Image.h"

class ImageTexture : public Texture
{
public:
	ImageTexture(char *file_name);
	virtual rgb Value(const Vector2 &uv, const Vector3 &pos) const override;

public:
	Image *image;
};

