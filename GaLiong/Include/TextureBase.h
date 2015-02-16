#pragma once
#include "Preprocess.h"

_L_BEGIN
class Texture;

class _L_ TextureBase
{
public:
	virtual const bool IsAvailable() = 0;
	virtual const bool IsInformative() = 0;
	virtual void Generate() = 0;
	virtual Texture &Get() = 0;
	virtual const unsigned char *GetData() = 0;
	virtual const GLuint GetIndex() = 0;
	virtual const unsigned char GetPixelLength() = 0;
	virtual const Size GetSize() = 0;
	virtual const bool SameType(WORD pixelFormat, WORD byteSize) = 0;
	virtual void Set(unsigned long dataLength, unsigned char *data, Size size, WORD pixelFormat, WORD byteSize) = 0;
private:
	bool isFromInstance;
};
_L_END