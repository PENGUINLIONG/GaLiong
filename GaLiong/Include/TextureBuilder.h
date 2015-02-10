#pragma once
#include "Preprocess.h"
#include "Texture.h"

_L_BEGIN
class _L_ TextureBuilder
{
public:
	TextureBuilder(WORD pixelFormat, WORD byteSize);
	bool AppendConponent(TextureConponent conponent);
	Texture *Make();
	~TextureBuilder();
private:
	int pxLength = 0;
	Rect boundary;
	WORD pixelFormat, byteSize;
	list<TextureConponent> textures;
};
_L_END