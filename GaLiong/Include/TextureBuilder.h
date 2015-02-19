#pragma once
#include "Preprocess.h"
#include "Texture.h"

_L_BEGIN
class _L_ TextureBuilder
{
public:
	TextureBuilder(TextureBase::PixelFormat pixelFormat, TextureBase::ByteSize byteSize);
	bool AppendConponent(TextureConponent conponent);
	Texture *Make();
	~TextureBuilder();
private:
	int pxLength = 0;
	Rect boundary;
	TextureBase::PixelFormat pixelFormat;
	TextureBase::ByteSize byteSize;
	list<TextureConponent> textures;
};
_L_END
