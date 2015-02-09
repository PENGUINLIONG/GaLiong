#pragma once
#include "Preprocess.h"

_L_BEGIN
class Texture;

interface _L_ ITexture
{
public:
	virtual inline Texture &Get() = 0;
	virtual inline void Set(unsigned long dataLength, unsigned char *data, Size size, WORD pixelFormat, WORD byteSize) = 0;
	virtual inline const unsigned char *GetData() = 0;
	virtual inline const Size GetSize() = 0;
	virtual inline const unsigned char GetPixelLength() = 0;
	virtual inline const bool IsAvailable() = 0;
	virtual inline const bool IsInformative() = 0;
	virtual inline const bool SameType(WORD pixelFormat, WORD byteSize) = 0;
protected:
	bool available = false;
	bool informative = false;
};
_L_END