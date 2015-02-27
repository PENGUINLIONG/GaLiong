#pragma once
#include "Preprocess.h"
#include "Texture.h"
#include "Logger.h"

_L_BEGIN
class _L_ TextureBuilder
{
public:
	TextureBuilder(TextureBase::PixelFormat pixelFormat, TextureBase::ByteSize byteSize);
	bool AppendConponent(TextureComponent conponent);
	void Make(TextureRef &target);
	~TextureBuilder();
private:
	int pxLength = 0;
	Rect boundary;
	TextureBase::PixelFormat pixelFormat;
	TextureBase::ByteSize byteSize;
	vector<TextureComponent> textures;
};
_L_END
