#pragma once
#include "Preprocess.h"
#include "Logger.h"
#include "Texture.h"
#include "TextureManager.h"

_L_BEGIN
class _L_ TextureBuilder
{
public:
	TextureBuilder(Flag pixelFormat, Flag byteSize);
	bool AppendConponent(TextureComponent conponent);
	TextureRef Make();
	~TextureBuilder();
private:
	int pxLength = 0;
	Rect boundary;
	Flag pixelFormat, byteSize;
	vector<TextureComponent> textures;
};
_L_END
