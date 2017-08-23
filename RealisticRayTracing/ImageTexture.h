#pragma once
#ifndef _IMAGE_TEXTURE_H_
#define _IMAGE_TEXTURE_H_

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

#endif // !_IMAGE_TEXTURE_H_

