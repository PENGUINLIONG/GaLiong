#pragma once
#include "Preprocess.h"

_L_BEGIN
class Texture;

interface _L_ TextureBase
{
public:
	virtual Texture &Get() = 0;
	virtual void Set(unsigned long dataLength, unsigned char *data, Size size, WORD pixelFormat, WORD byteSize) = 0;
	virtual const unsigned char *GetData() = 0;
	virtual const Size GetSize() = 0;
	virtual const unsigned char GetPixelLength() = 0;
	virtual const bool IsAvailable() = 0;
	virtual const bool IsInformative() = 0;
	virtual const bool SameType(WORD pixelFormat, WORD byteSize) = 0;
};
_L_END