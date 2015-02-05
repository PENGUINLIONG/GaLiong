#pragma once
#include <vector>
#include "Preprocess.h"
#include "Texture.h"

_L_BEGIN
typedef struct
{
	Rect Rect;
	Texture *Texture;
} TextureConponent;

class _L_ TextureBuilder
{
public:
	TextureBuilder(WORD pixelFormat, WORD byteSize);
	TextureBuilder(WORD pixelFormat, WORD byteSize, Size deadline);
	bool AppendConponent(TextureConponent conponent);
	Texture *Make();
	~TextureBuilder();
private:
	int pxLength = 0;
	Rect boundary;
	WORD pixelFormat, byteSize;
	vector<TextureConponent> textures;
};
_L_END