#pragma once
#include "Preprocess.hpp"
#include "Texture.hpp"

_L_BEGIN
class _L_ TextureManagerImpl
{
public:
	TextureManagerImpl();
	~TextureManagerImpl();
	void DeleteTexture(TextureRef target);

	TextureRef NewTexture();
	TextureRef NewTexture(BufferLength dataLength, Buffer data, Size size, Flag pixelFormat, Flag byteSize);
private:
	list<TextureStrongRef> refs;
};
static TextureManagerImpl TextureManager;
_L_END